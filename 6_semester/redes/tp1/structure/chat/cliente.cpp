#include "common.h"
#include "console.hpp"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

using namespace std;

#define BUFSZ 1024

int s;

void usage(int argc, char **argv) {
    printf("usage: %s <server IP> <server port>\n", argv[0]);
    printf("example: %s 127.0.0.1 51511\n", argv[0]);
    exit(EXIT_FAILURE);
}

void *recv_thread(Flags &shared) {
    size_t count;
    unsigned total = 0;
    char buf[BUFSZ];
    memset(buf, 0, BUFSZ);

    while (strchr(buf, '\n') == NULL && total <= 500) {
        for (int i = 0; i < strlen(buf); i++) {
            printf("%d ", buf[i]);
        }
        printf("\n");
        count = recv(s, buf + total, BUFSZ - total, 0);
        if (count == 0) {
            break;
        }
        total += count;
        shared.console.write(buf);
    }

    pthread_exit(EXIT_SUCCESS);
}

void *recv_thread2(void *data) {
    Flags *shared = static_cast<Flags *>(data);
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

    shared->console.write(buf);

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

    size_t count;

    Flags shared;
    void *pv = &shared;

    // std::thread threadProc(&recv_thread, std::ref(shared));

    while (1) {
        pthread_t tid;
        pthread_create(&tid, NULL, recv_thread2, pv);

        std::string input = shared.console.read();

        count = send(s, input.c_str(), strlen(input.c_str()) + 1, 0);
        if (count != strlen(input.c_str()) + 1) {
            logexit("send");
        }
    }

    // threadProc.join();
    close(s);
    exit(EXIT_SUCCESS);
}