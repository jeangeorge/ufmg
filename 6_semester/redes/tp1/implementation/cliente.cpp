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

void usage(int argc, char **argv)
{
	printf("usage: %s <server IP> <server port>\n", argv[0]);
	printf("example: %s 127.0.0.1 51511\n", argv[0]);
	exit(EXIT_FAILURE);
}

// Metodo para enviar mensagen para o servidor
void send_message(string input)
{
	// Primeiro trata a mensagem, convertendo de string e adicionando um \n no fim
	char buf[BUFSZ];
	memset(buf, 0, BUFSZ);
	for (unsigned int i = 0; i < input.size(); i++)
	{
		buf[i] = input[i];
	}
	buf[strlen(buf)] = '\n';

	// Envia
	size_t count = send(s, buf, strlen(buf), 0);
	if (count != strlen(buf))
	{
		logexit("send");
	}
}

// Metodo para receber constatemente mensagens do servidor
void *receive_message(Flags &shared)
{
	char buf[BUFSZ];
	while (1)
	{
		memset(buf, 0, BUFSZ);
		size_t count = 0;
		unsigned total = 0;
		while (1)
		{
			count = recv(s, buf + total, BUFSZ - total, 0);

			if (count == 0)
			{
				exit(EXIT_SUCCESS);
				break;
			}

			total += count;

			if (is_valid_message(buf) == 0)
			{
				exit(EXIT_SUCCESS);
				break;
			}

			if (buf[total - 1] == '\n')
			{
				break;
			}
		}
		shared.console.write(buf);
	}
}

int main(int argc, char **argv)
{
	if (argc < 3)
	{
		usage(argc, argv);
	}

	struct sockaddr_storage storage;
	if (0 != addrparse(argv[1], argv[2], &storage))
	{
		usage(argc, argv);
	}

	s = socket(storage.ss_family, SOCK_STREAM, 0);
	if (s == -1)
	{
		logexit("socket");
	}

	struct sockaddr *addr = (struct sockaddr *)(&storage);
	if (0 != connect(s, addr, sizeof(struct sockaddr)))
	{
		logexit("connect");
	}

	char addrstr[BUFSZ];
	addrtostr(addr, addrstr, BUFSZ);

	printf("connected to %s\n", addrstr);

	Flags shared;

	thread thread_recv(&receive_message, ref(shared));

	while (1)
	{
		string input = shared.console.read();
		send_message(input);
	}

	thread_recv.join();
	close(s);
	exit(EXIT_SUCCESS);
	return 0;
}