#include "common.h"

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
		// Cria storage e endereço para o cliente
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

		// Converte e printa o endereço do cliente
		char caddrstr[BUFSZ];
		addrtostr(caddr, caddrstr, BUFSZ);
		printf("[log] connection from %s\n", caddrstr);

		// Ler a mensagem do cliente
		// Cria um buffer para ler e lê
		char buf[BUFSZ];
		memset(buf, 0, BUFSZ);
		size_t count = recv(csock, buf, BUFSZ - 1, 0);
		printf("[msg] %s, %d bytes: %s\n", caddrstr, (int)count, buf);

		// Pŕinta no buf e envia de volta pelo csock
		sprintf(buf, "remote endpoint: %.1000s\n", caddrstr);
		count = send(csock, buf, strlen(buf) + 1, 0);
		if (count != strlen(buf) + 1)
		{
			logexit("send");
		}
		close(csock);
	}

	exit(EXIT_SUCCESS);
}