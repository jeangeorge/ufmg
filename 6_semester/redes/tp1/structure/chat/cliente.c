#include "common.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

void usage(int argc, char **argv) {
    printf("usage: %s <server IP> <server port>\n", argv[0]);
    printf("example: %s 127.0.0.1 51511\n", argv[0]);
    exit(EXIT_FAILURE);
}

#define BUFSZ 1024

void *recv_thread(void *data) {
    int s = (intptr_t)data;
    size_t count;
    unsigned total = 0;
    char buf[BUFSZ];
    memset(buf, 0, BUFSZ);

    while (strchr(buf, '\n') == NULL && total <= 500) {
        if (strcmp(buf, "##kill\n") == 0) {
            close(s);
            exit(EXIT_SUCCESS);
        }
        count = recv(s, buf + total, BUFSZ - total, 0);
        if (count == 0) {
            break;
        }
        total += count;
    }

    printf("%s", buf);

    pthread_exit(EXIT_SUCCESS);
}

int main(int argc, char **argv) {
    if (argc < 3) {
        usage(argc, argv);
    }

    struct sockaddr_storage storage;
    if (0 != addrparse(argv[1], argv[2], &storage)) {
        usage(argc, argv);
    }

    int s;
    s = socket(storage.ss_family, SOCK_STREAM, 0);
    if (s == -1) {
        logexit("socket");
    }
    struct sockaddr *addr = (struct sockaddr *)(&storage);
    if (0 != connect(s, addr, sizeof(struct sockaddr))) {
        logexit("connect");
    }

    char addrstr[BUFSZ];
    addrtostr(addr, addrstr, BUFSZ);

    printf("connected to %s\n", addrstr);

    char buf[BUFSZ];
    memset(buf, 0, BUFSZ);

    size_t count;

    while (1) {
        pthread_t tid;
        pthread_create(&tid, NULL, recv_thread, (void *)(intptr_t)s);
        memset(buf, 0, BUFSZ);
        printf("> ");
        fgets(buf, BUFSZ - 1, stdin);
        count = send(s, buf, strlen(buf) + 1, 0);
        if (count != strlen(buf) + 1) {
            logexit("send");
        }
    }

    close(s);

    exit(EXIT_SUCCESS);
}