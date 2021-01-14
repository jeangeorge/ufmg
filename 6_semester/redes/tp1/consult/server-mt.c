#include "common.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/types.h>

#define BUFSZ 1024

void usage(int argc, char **argv)
{
	printf("usage: %s <v4|v6> <server port>\n", argv[0]);
	printf("example: %s v4 51511\n", argv[0]);
	exit(EXIT_FAILURE);
}

struct client_data
{
	int csock;
	struct sockaddr_storage storage;
};

void *client_thread(void *data)
{
	// Pega os dados
	struct client_data *cdata = (struct client_data *)data;
	struct sockaddr *caddr = (struct sockaddr *)(&cdata->storage);

	// Mostra o endereço do cliente
	char caddrstr[BUFSZ];
	addrtostr(caddr, caddrstr, BUFSZ);
	printf("[log] connection from %s\n", caddrstr);

	// Cria um buf e inicialzia ele
	char buf[BUFSZ];
	memset(buf, 0, BUFSZ);

	// Chama o receive para receber os dados e mostra o que foi recebido
	size_t count = recv(cdata->csock, buf, BUFSZ - 1, 0);
	printf("[msg] %s, %d bytes: %s\n", caddrstr, (int)count, buf);

	// Printa os dados na variavel buf e a  retorna para o cliente
	sprintf(buf, "remote endpoint: %.1000s\n", caddrstr);
	count = send(cdata->csock, buf, strlen(buf) + 1, 0);
	if (count != strlen(buf) + 1)
	{
		logexit("send");
	}
	close(cdata->csock);

	pthread_exit(EXIT_SUCCESS);
}

// Recebe o tipo de protocolo servidor e o porto onde vai ficar esperando
int main(int argc, char **argv)
{
	if (argc < 3)
	{
		usage(argc, argv);
	}

	// Inicializa o storage do servidor
	struct sockaddr_storage storage;
	if (0 != server_sockaddr_init(argv[1], argv[2], &storage))
	{
		usage(argc, argv);
	}

	// Cria o socket
	int s;
	s = socket(storage.ss_family, SOCK_STREAM, 0);
	if (s == -1)
	{
		logexit("socket");
	}

	// Adiciona a opção no socket para reutilizar a porta do servidor
	int enable = 1;
	if (0 != setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)))
	{
		logexit("setsockopt");
	}

	struct sockaddr *addr = (struct sockaddr *)(&storage);
	// Chama o bind, passando o socket a estrutura socaddr e o tamanho dela
	if (0 != bind(s, addr, sizeof(storage)))
	{
		logexit("bind");
	}

	// Chama o listen passando o socket e a quantidade de conexões que podem estar presentes para tratamento
	if (0 != listen(s, 10))
	{
		logexit("listen");
	}

	// Converte o addr para string e mostra uma mensagem
	char addrstr[BUFSZ];
	addrtostr(addr, addrstr, BUFSZ);
	printf("bound to %s, waiting connections\n", addrstr);

	// Loop para tratamento dos clientes
	while (1)
	{
		struct sockaddr_storage cstorage;
		struct sockaddr *caddr = (struct sockaddr *)(&cstorage);
		socklen_t caddrlen = sizeof(cstorage);

		// Chama o accept passando o socket, o endereço do cliente e o tamanho do endereço do cliente.
		// Retorna o socket do cliente, é o que conversa com o cliente
		int csock = accept(s, caddr, &caddrlen);
		if (csock == -1)
		{
			// trata erro de conexão
			logexit("accept");
		}

		// Cria uma struct data para enviar os dados para a thread
		struct client_data *cdata = malloc(sizeof(*cdata));
		// Se não malocar a memória cai fora
		if (!cdata)
		{
			logexit("malloc");
		}
		// Seta os atributos do data
		cdata->csock = csock;
		memcpy(&(cdata->storage), &cstorage, sizeof(cstorage));

		// Cria uma thread passando a rotina que será rodada em separado na thread
		pthread_t tid;
		pthread_create(&tid, NULL, client_thread, cdata);
	}

	exit(EXIT_SUCCESS);
}
