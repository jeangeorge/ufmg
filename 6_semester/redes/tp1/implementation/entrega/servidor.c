#include "common.h"

#include <string.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/types.h>

#define BUFSZ 1024

void usage(int argc, char **argv)
{
	printf("usage: %s <server port>\n", argv[0]);
	printf("example: %s 51511\n", argv[0]);
	exit(EXIT_FAILURE);
}

struct client_data
{
	int csock;
	struct sockaddr_storage storage;
	int tags_number;
	char **tags;
	int connected;
};

int clients_number = 0;
struct client_data **clients;

// Obter tag de interesse: metodo chamado caso seja uma msg de subscribe/unsubscribe, retorna a tag por referencia na variavel tag
int get_interest_tag(char *msg, char *tag)
{
	int i = 1, tagSize = 0;
	while (msg[i] != '\n')
	{
		if (is_valid_char(msg[i]) == 0)
		{
			return 0;
		}
		tagSize++;
		tag = realloc(tag, tagSize * sizeof(char));
		tag[i - 1] = msg[i];
		i++;
	}
	return 1;
}

// Funcao para verificar se um cliente está inscrito na tag
// Recebe a posição no array de clientes e a tag a ser verificada
int already_subscribed(const int client_pos, char *tag)
{
	for (int j = 0; j < clients[client_pos]->tags_number; j++)
	{
		if (strcmp(clients[client_pos]->tags[j], tag) == 0)
		{
			return 1;
		}
	}
	return 0;
}

// Função para inscrever uma tag num cliente
// Recebe a posição no array de clientes e a tag a ser inscrita
void subscribe_tag(const int client_pos, char *tag)
{
	clients[client_pos]->tags_number++;
	clients[client_pos]->tags =
		realloc(clients[client_pos]->tags, clients[client_pos]->tags_number);
	clients[client_pos]->tags[clients[client_pos]->tags_number - 1] = tag;
}

// Função para desinscrever uma tag num cliente
// Recebe a posição no array de clientes e a tag a ser desinscrita
void unsubscribe_tag(const int client_pos, char *tag)
{
	// Cria um array de tags auxiliar
	int tags_number = 0;
	char **tags = malloc(tags_number * sizeof(char *));
	// Percorre o array de tags do cliiente
	for (int i = 0; i < clients[client_pos]->tags_number; i++)
	{
		// Adiciona no array auxiliar todas as tags que nao sejam a que estamos removendo
		if (strcmp(clients[client_pos]->tags[i], tag) != 0)
		{
			tags_number++;
			tags = realloc(tags, tags_number);
			tags[tags_number - 1] = clients[client_pos]->tags[i];
		}
	}
	// Atualiza as referenciais no array de clientes
	clients[client_pos]->tags = tags;
	clients[client_pos]->tags_number = tags_number;
}

// Função para verificar se uma tag é válida
int is_valid_tag(char *tag)
{
	// Percorre a tag caracter a caracter
	for (int i = 1; i < strlen(tag); i++)
	{
		// Verifica se ela possui algum caracter invalido
		if (is_valid_char(tag[i]) == 0)
		{
			return 0;
		}
	}
	return 1;
}

// Função para disparar para todos os clientes inscritos na tag uma msg
void dispatch_to_clients(char *msg, char *tag)
{
	// Já cria o buffer colocando a mensagem nele
	char buf[BUFSZ];
	memset(buf, 0, BUFSZ);
	sprintf(buf, "%.1000s\n", msg);

	size_t count;

	// Percorre todos os clientes
	for (int i = 0; i < clients_number; i++)
	{
		// Filtra os clientes conectados
		if (clients[i]->connected == 1)
		{
			// Um a um, verifica se ele ele esta inscrito na tag
			if (already_subscribed(i, tag))
			{
				// Se estiver, envia a mensagem pra ele
				count = send(clients[i]->csock, buf, strlen(buf), 0);
				if (count != strlen(buf))
				{
					logexit("send");
				}
			}
		}
	}
}

// Função para tratar o recebimento de tags
void handle_tag(const int client_pos, char *msg)
{
	// Cliente desconectado cai fora
	if (clients[client_pos]->connected == 0)
	{
		return;
	}
	char buf[BUFSZ];
	memset(buf, 0, BUFSZ);

	// Tenta pegar a tag
	char *tag = malloc(0 * sizeof(char));
	if (get_interest_tag(msg, tag) == 1)
	{
		// Caso seja subscribe
		if (msg[0] == '+')
		{
			// Se nao esta inscrito, inscreve
			if (already_subscribed(client_pos, tag) == 0)
			{
				subscribe_tag(client_pos, tag);
				sprintf(buf, "subscribed +%.1000s\n", tag);
			}
			else
			{
				sprintf(buf, "already subscribed +%.1000s\n", tag);
			}
		}
		else
		{
			// Caso seja unsubscribe
			if (already_subscribed(client_pos, tag) == 1)
			{
				// Se ja esta inscrito, desinscreve
				unsubscribe_tag(client_pos, tag);
				sprintf(buf, "unsubscribed -%.1000s\n", tag);
			}
			else
			{
				sprintf(buf, "not subscribed -%.1000s\n", tag);
			}
		}
	}

	// Envia a mensagem pro client coreto
	size_t count = send(clients[client_pos]->csock, buf, strlen(buf), 0);
	if (count != strlen(buf))
	{
		logexit("send");
	}
}

// Função para tratar a msg caso seja uma mensagem comum
void handle_message(char *msg)
{
	// Verifica se existe o caractere # na mensagem, se nao tiver cai fora já que msg sem # nao sao processadas
	if (strchr(msg, '#') == NULL)
	{
		return;
	}

	// Array de menssagens
	char **messages = malloc(0 * sizeof(char *));
	int total_messages = 0;

	// Separa a mensagem por \n e vai colocando em messages
	char *message = strtok(msg, "\n");
	while (message != NULL)
	{
		total_messages++;
		messages[total_messages - 1] = message;
		message = strtok(NULL, "\n");
	}

	// Separa cada mensagem por espaço
	for (int i = 0; i < total_messages; i++)
	{
		// Salva a mensagem original para envia-la corretamente
		char *original_message = malloc((strlen(messages[i])) * sizeof(char));
		strcpy(original_message, messages[i]);

		// Separa a mensagem por espaço
		char *word = strtok(messages[i], " ");
		while (word != NULL)
		{
			// Caso a palavra comece com # se trata de uma tag
			if (word[0] == '#')
			{
				// Caso a tag seja valida
				if (is_valid_tag(word))
				{
					// Chama o metodo dispatch to clientes para disparar a mensagem para os clientes com determinada tag
					dispatch_to_clients(original_message, word + 1);
				}
			}
			word = strtok(NULL, " ");
		}
	}
}

// Metodo para disconectar todos clientes
void disconect_all()
{
	for (int i = 0; i < clients_number; i++)
	{
		clients[i]->connected = 0;
		close(clients[i]->csock);
	}
}

// Metodo para disconectar um unico cliente
void disconect_one(const int client_pos, char *caddrstr)
{
	// Fecha a conexão do cliente
	clients[client_pos]->connected = 0;
	close(clients[client_pos]->csock);
	printf("[log] client %s disconnected\n", caddrstr);
}

// Função chamada pela thread para receber constantemente dados de clientes
void *client_thread(void *data)
{
	int client_pos = (intptr_t)data;
	char buf[BUFSZ];

	// Mostra o endereço do cliente
	char caddrstr[BUFSZ];
	addrtostr((struct sockaddr *)(&clients[client_pos]->storage), caddrstr, BUFSZ);
	printf("[log] connection from %s\n", caddrstr);

	while (1)
	{
		// Cria um buf e inicialzia ele
		memset(buf, 0, BUFSZ);
		size_t count = 0;
		unsigned total = 0;
		// Chama o receive para receber os dados e mostra o que foi recebido
		while (1)
		{
			count = recv(clients[client_pos]->csock, buf + total, BUFSZ - total, 0);
			if (count == 0)
			{
				break;
			}
			total += count;
			if (is_valid_message(buf) == 0)
			{
				printf("[log] invalid message received from %s, client will be disconnected\n", caddrstr);
				disconect_one(client_pos, caddrstr);
				break;
			}
			// Verifica se deve encerrar o servidor
			if (strcmp(buf, "##kill\n") == 0)
			{
				printf("[log] kill message received from %s, all clients will be disconnected\n", caddrstr);
				disconect_all();
				exit(EXIT_SUCCESS);
				break;
			}

			if (buf[total - 1] == '\n')
			{
				break;
			}
		}
		if (total == 0)
		{
			disconect_one(client_pos, caddrstr);
			break;
		}
		printf("[msg] %s, %d bytes: %s\n", caddrstr, (int)count, buf);
		// Verificação de subscribe/unsubscribe
		if (buf[0] == '+' || buf[0] == '-')
		{
			// Se for, trata no metodo handle_tag
			handle_tag(client_pos, buf);
		}
		else
		{
			// Se nao for subscribe/unsubscribe é uma mensagem normal, trata ela no metodo handle_message
			handle_message(buf);
		}
	}
	close(clients[client_pos]->csock);
	pthread_exit(EXIT_SUCCESS);
}

// Recebe o tipo de protocolo servidor e o porto onde vai ficar esperando
int main(int argc, char **argv)
{
	if (argc < 2)
	{
		usage(argc, argv);
	}

	// Inicializa o vetor de clients com 0
	clients = malloc(clients_number * sizeof(struct client_data *));

	// Inicializa o storage do servidor
	struct sockaddr_storage storage;
	if (0 != server_sockaddr_init("v4", argv[1], &storage))
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
	if (0 != bind(s, addr, sizeof(struct sockaddr)))
	{
		logexit("bind");
	}

	// Chama o listen passando o socket e a quantidade de conexões que podem
	// estar presentes para tratamento
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

		// Chama o accept passando o socket, o endereço do cliente e o
		// tamanho do endereço do cliente. Retorna o socket do cliente, é o
		// que conversa com o cliente
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

		cdata->tags = malloc(0 * sizeof(char *));
		cdata->tags_number = 0;
		cdata->connected = 1;

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
