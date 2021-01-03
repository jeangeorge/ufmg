#include "common.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

// Método para mostrar ao usuário como rodar o programa
// É chamado quando o usuário inicializa o programa incorretamente
void usage(int argc, char **argv)
{
	printf("usage: %s <server IP> <server port>\n", argv[0]);
	printf("example: %s 127.0.0.1 51511\n", argv[0]);
	exit(EXIT_FAILURE);
}

#define BUFSZ 1024

// Recebe como parâmetro o IP do servidor e o porto
int main(int argc, char **argv)
{
	// Verifica se o programa foi chamado corretamente
	if (argc < 3)
	{
		usage(argc, argv);
	}

	// Define o storage fazendo a conversão: inicializa ele com o endereço e porto recebidos via argumentos
	struct sockaddr_storage storage;
	// Caso não consiga fazer o parse cai fora
	if (0 != addrparse(argv[1], argv[2], &storage))
	{
		usage(argc, argv);
	}

	// Primeiramente é preciso abrir um socket de conexão
	// Argumento 1: família, pode ser ipv4 ou ipv6
	// Argumento 2: SOCK_STREAM indica que é TCP
	int s;
	s = socket(storage.ss_family, SOCK_STREAM, 0);
	if (s == -1)
	{
		// Caso a abertura do socket tenha dado erro, imprime o erro e sai do programa
		logexit("socket");
	}

	// Obtendo o endereço do servidor
	// Inicializa o ponteiro fazendo o cast do storage
	struct sockaddr *addr = (struct sockaddr *)(&storage);
	// Depois do socket é necessário chamar o connect
	// Chama o connect passando o socket, o endereço do servidor e o tamanho do endereço?
	if (0 != connect(s, addr, sizeof(storage)))
	{
		// Se deu erro cai fora
		logexit("connect");
	}

	// Convertendo o endereço para string
	char addrstr[BUFSZ];
	addrtostr(addr, addrstr, BUFSZ);

	printf("connected to %s\n", addrstr);

	// Início da comunicação cliente-servidor
	// Cria um buffer (que é utilizado para enviar/receber) e inicializa com 0
	char buf[BUFSZ];
	memset(buf, 0, BUFSZ);

	// Lê a mensagem do usário a partir do teclado
	printf("mensagem> ");
	fgets(buf, BUFSZ - 1, stdin);

	// Enviando pro servidor
	// Manda o socket, o dado, número de bytes que está sendo mandado (tamanho do texto + 1), 0 -> sem opções especiais
	// Send retorna para o count o número de bytes que foram transmitidos na rede
	size_t count = send(s, buf, strlen(buf) + 1, 0);
	// Portanto, caso que esteja no count seja de tamanho diferente do que foi mandado cai fora
	if (count != strlen(buf) + 1)
	{
		logexit("send");
	}

	// Recebendo do servidor
	// Reseta o buf
	memset(buf, 0, BUFSZ);

	// Contador para saber o total de dados recebidos até o momento
	unsigned total = 0;

	// While 1 pra ficar recebendo constantemente
	// Recebe dados de pouco em pouco e vai colocando no buf, até não receber mais nada.
	while (1)
	{
		// Chama a função receive para receber o dado
		// Utiliza o socket s, coloca na variável buf e indica a quantidade de dados transmitidos
		// 'total' é utilizado porque o servidor pode mandar os dados separadamente
		// A medida que o dado chega, desloca o ponteiro do buf 'total' posições para receber o dado
		// Recebe sempre BUFSZ - total
		count = recv(s, buf + total, BUFSZ - total, 0);
		// Caso o recv retorne 0 é porque a conexão está fechada, portanto cai fora
		if (count == 0)
		{
			// Connection terminated.
			break;
		}
		// Atualiza o total
		total += count;
	}
	close(s);

	printf("received %u bytes\n", total);
	puts(buf);

	exit(EXIT_SUCCESS);
}