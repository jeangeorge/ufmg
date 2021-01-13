#include "common.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/types.h>

#define BUFSZ 1024

void usage(int argc, char **argv) {
    printf("usage: %s <v4|v6> <server port>\n", argv[0]);
    printf("example: %s v4 51511\n", argv[0]);
    exit(EXIT_FAILURE);
}

struct client_data {
    int csock;
    struct sockaddr_storage storage;
    int tags_number;
    char **tags;
};

int clients_number = 0;
struct client_data **clients;

int running = 1;

void show_clients() {
    for (int i = 0; i < clients_number; i++) {
        printf("CLIENT %d\n", clients[i]->csock);
        printf("TAGS DE INTERESSE\n");
        for (int j = 0; j < clients[i]->tags_number; j++) {
            printf("%s\n", clients[i]->tags[j]);
        }
    }
}

int is_valid_char(char c) {
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
        (c >= '0' && c <= '9') || ((int)c == 0)) {
        return 1;
    } else {
        return 0;
    }
}

int get_interest_tag(char *msg, char *tag) {
    int i = 1, tagSize = 0;
    while (msg[i] != '\0') {
        if (is_valid_char(msg[i]) == 0) {
            return 0;
        }
        tagSize++;
        tag = realloc(tag, tagSize * sizeof(char));
        tag[i - 1] = msg[i];
        i++;
    }
    return 1;
}

int already_subscribed(struct client_data *client, char *tag) {
    for (int i = 0; i < client->tags_number; i++) {
        if (strcmp(client->tags[i], tag) == 0) {
            return 1;
        }
    }
    return 0;
}

void subscribe_tag(struct client_data *client, char *tag) {
    for (int i = 0; i < clients_number; i++) {
        if (clients[i]->csock == client->csock) {
            clients[i]->tags_number++;
            clients[i]->tags =
                realloc(clients[i]->tags, clients[i]->tags_number);
            clients[i]->tags[clients[i]->tags_number - 1] = tag;
        }
    }
}

void unsubscribe_tag(struct client_data *client, char *tag) {
    for (int i = 0; i < clients_number; i++) {
        if (clients[i]->csock == client->csock) {
            int tags_number = 0;
            char **tags = malloc(0 * sizeof(char *));
            for (int j = 0; j < clients[i]->tags_number; j++) {
                if (strcmp(clients[i]->tags[j], tag) != 0) {
                    tags_number++;
                    tags = realloc(tags, tags_number);
                    tags[tags_number - 1] = clients[i]->tags[j];
                }
            }
            clients[i]->tags = tags;
            clients[i]->tags_number = tags_number;
        }
    }
}

int is_valid_tag(char *tag) {
    for (int i = 1; i < strlen(tag); i++) {
        if (is_valid_char(tag[i]) == 0) {
            return 0;
        }
    }
    return 1;
}

void dispatch_to_clients(char *msg, char *tag) {
    printf("msg :::::::::: %s\n", msg);
    printf("tag :::::::::: %s\n", tag);
    size_t count;
    char buf[BUFSZ];
    memset(buf, 0, BUFSZ);
    sprintf(buf, "%.1000s\n", msg);
    for (int i = 0; i < clients_number; i++) {
        if (already_subscribed(clients[i], tag)) {
            printf("client %d ta com sub\n", clients[i]->csock);
            printf("enviar -> %s <- pro client\n", buf);
            count = send(clients[i]->csock, buf, strlen(buf) + 1, 0);
            if (count != strlen(buf) + 1) {
                logexit("send");
            }
        } else {
            printf("client %d n ta com sub\n", clients[i]->csock);
        }
    }
}

void handle_message(struct client_data *client, char *msg) {
    // Verifica se existe o caractere # na mensagem, se nao tiver cai fora
    if (strchr(msg, '#') == NULL) {
        return;
    }

    char **messages = malloc(0 * sizeof(char *));
    int total_messages = 0;

    // Separa a mensagem por \n
    char *message = strtok(msg, "\n");
    while (message != NULL) {
        total_messages++;
        messages[total_messages - 1] = message;
        message = strtok(NULL, "\n");
    }

    // Separa cada mensagem por espaço
    for (int i = 0; i < total_messages; i++) {
        char *original_message = malloc(strlen(messages[i]) * sizeof(char));
        strcpy(original_message, messages[i]);
        // Separa a mensagem por espaço
        char *word = strtok(messages[i], " ");
        while (word != NULL) {
            // Pega as palavras que começam por #
            if (word[0] == '#') {
                printf("word: %s \n", word);
                if (is_valid_tag(word)) {
                    printf("deu bom\n");
                    // Dispara a tag sem # para os clientes
                    dispatch_to_clients(original_message, word + 1);
                } else {
                    printf("dfeu ruim\n");
                }
            }
            word = strtok(NULL, " ");
        }
    }
}

void disconect_all() {
    for (int i = 0; i < clients_number; i++) {
        close(clients[i]->csock);
    }
}

void *client_thread(void *data) {
    int i = (intptr_t)data;

    // Mostra o endereço do cliente
    char caddrstr[BUFSZ];
    addrtostr((struct sockaddr *)(&clients[i]->storage), caddrstr, BUFSZ);
    printf("[log] connection from %s\n", caddrstr);

    // Cria um buf e inicialzia ele
    char buf[BUFSZ];
    memset(buf, 0, BUFSZ);
    size_t count;

    // Chama o receive para receber os dados e mostra o que foi recebido
    while (1) {
        memset(buf, 0, BUFSZ);
        count = recv(clients[i]->csock, buf, BUFSZ - 1, 0);

        // Verifica se deve encerrar o servidor
        if (strcmp(buf, "##kill\n") == 0) {
            running = 0;
            disconect_all();
            exit(EXIT_SUCCESS);
            break;
        }

        printf("[msg] %s, %d bytes: %s\n", caddrstr, (int)count, buf);

        // Verificação de subscribe/unsubscribe
        if (buf[0] == '+' || buf[0] == '-') {
            char *tag = malloc(0 * sizeof(char));
            if (get_interest_tag(buf, tag) == 1) {
                if (buf[0] == '+') {
                    if (already_subscribed(clients[i], tag) == 0) {
                        subscribe_tag(clients[i], tag);
                        printf("subscribed +%.1000s\n", tag);
                        sprintf(buf, "subscribed +%.1000s\n", tag);
                    } else {
                        sprintf(buf, "already subscribed +%.1000s\n", tag);
                    }
                } else {
                    if (already_subscribed(clients[i], tag) == 1) {
                        unsubscribe_tag(clients[i], tag);
                        sprintf(buf, "unsubscribed -%.1000s\n", tag);
                    } else {
                        sprintf(buf, "not subscribed -%.1000s\n", tag);
                    }
                }
            }
            count = send(clients[i]->csock, buf, strlen(buf) + 1, 0);
            if (count != strlen(buf) + 1) {
                logexit("send");
            }
        } else {
            handle_message(clients[i], buf);
        }
    }
    close(clients[i]->csock);

    pthread_exit(EXIT_SUCCESS);
}

// Recebe o tipo de protocolo servidor e o porto onde vai ficar esperando
int main(int argc, char **argv) {
    if (argc < 3) {
        usage(argc, argv);
    }

    // Inicializa o vetor de clients com 0
    clients = malloc(clients_number * sizeof(struct client_data *));

    // Inicializa o storage do servidor
    struct sockaddr_storage storage;
    if (0 != server_sockaddr_init(argv[1], argv[2], &storage)) {
        usage(argc, argv);
    }

    // Cria o socket
    int s;
    s = socket(storage.ss_family, SOCK_STREAM, 0);
    if (s == -1) {
        logexit("socket");
    }

    // Adiciona a opção no socket para reutilizar a porta do servidor
    int enable = 1;
    if (0 != setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int))) {
        logexit("setsockopt");
    }

    struct sockaddr *addr = (struct sockaddr *)(&storage);
    // Chama o bind, passando o socket a estrutura socaddr e o tamanho dela
    if (0 != bind(s, addr, sizeof(struct sockaddr))) {
        logexit("bind");
    }

    // Chama o listen passando o socket e a quantidade de conexões que podem
    // estar presentes para tratamento
    if (0 != listen(s, 10)) {
        logexit("listen");
    }

    // Converte o addr para string e mostra uma mensagem
    char addrstr[BUFSZ];
    addrtostr(addr, addrstr, BUFSZ);
    printf("bound to %s, waiting connections\n", addrstr);

    // Loop para tratamento dos clientes
    while (1) {
        if (running != 1) {
            exit(EXIT_SUCCESS);
            break;
        }

        struct sockaddr_storage cstorage;
        struct sockaddr *caddr = (struct sockaddr *)(&cstorage);
        socklen_t caddrlen = sizeof(cstorage);

        // Chama o accept passando o socket, o endereço do cliente e o
        // tamanho do endereço do cliente. Retorna o socket do cliente, é o
        // que conversa com o cliente
        int csock = accept(s, caddr, &caddrlen);
        if (csock == -1) {
            // trata erro de conexão
            logexit("accept");
        }

        // Cria uma struct data para enviar os dados para a thread
        struct client_data *cdata = malloc(sizeof(*cdata));
        // Se não malocar a memória cai fora
        if (!cdata) {
            logexit("malloc");
        }

        // Seta os atributos do data
        cdata->csock = csock;
        memcpy(&(cdata->storage), &cstorage, sizeof(cstorage));

        cdata->tags = malloc(0 * sizeof(char *));
        cdata->tags_number = 0;

        clients_number++;
        clients[clients_number - 1] = cdata;

        // Cria uma thread passando a rotina que será rodada em separado na
        // thread
        pthread_t tid;
        pthread_create(&tid, NULL, client_thread,
                       (void *)(intptr_t)(clients_number - 1));
    }

    exit(EXIT_SUCCESS);
}
