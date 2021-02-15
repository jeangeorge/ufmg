#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <arpa/inet.h>

// Mostra mensagem de erro e fecha o programa
void logexit(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

/*
	Faz o parse: coloca o endereço e o porto dentro do storage
*/
int addrparse(const char *addrstr, const char *portstr,
			  struct sockaddr_storage *storage)
{
	// Valida o endereço e o porto
	if (addrstr == NULL || portstr == NULL)
	{
		return -1;
	}

	// uint16_t == unsigned short. É 16 bits por definição: foi definido que o porto da internet tem esse tamanho.
	// Converte a string int, faz o cast e joga na variável poort
	uint16_t port = (uint16_t)atoi(portstr);
	// Igual a zero é porque não converteu ou o endereço é 0
	if (port == 0)
	{
		return -1;
	}

	// host to network short
	// É necessário fazer essa chamada porque o número da porta é sempre big endian e o dispositivo envia um little endia, o htons faz essa conversão
	port = htons(port);

	// Aqui já temos a porta convertida, é preciso converter o endereçõ
	// Vamos tentar converter primeiro para ipv4, se não der tenta converter para ipv6
	struct in_addr inaddr4; // 32-bit IP address
	// Tenta fazer o parse
	if (inet_pton(AF_INET, addrstr, &inaddr4))
	{
		// Se der certo é porque é ipv4, joga na variável addr4
		// addr4 é um ponteiro que aponta para storage
		struct sockaddr_in *addr4 = (struct sockaddr_in *)storage;
		// Faz a inicialização do addr4 e consequentemente do storage
		addr4->sin_family = AF_INET;
		addr4->sin_port = port;
		addr4->sin_addr = inaddr4;
		return 0;
	}

	// Para o ipv6 é a mesma coisa, só muda no endereço por se tratar de um arranjo, é preciso fazer o memcpy para copiar os 16 bytes na marra
	struct in6_addr inaddr6; // 128-bit IPv6 address
	if (inet_pton(AF_INET6, addrstr, &inaddr6))
	{
		struct sockaddr_in6 *addr6 = (struct sockaddr_in6 *)storage;
		addr6->sin6_family = AF_INET6;
		addr6->sin6_port = port;
		memcpy(&(addr6->sin6_addr), &inaddr6, sizeof(inaddr6));
		return 0;
	}

	return -1;
}

// Converte um sockaddr para string, recebe o sockaddr, a string e o tamanho da string
void addrtostr(const struct sockaddr *addr, char *str, size_t strsize)
{
	int version;							 // O endereço pode ser ipv4 ou ipv6
	char addrstr[INET6_ADDRSTRLEN + 1] = ""; // Cria um array de caracteres de tamanaho máximo de um endereço ipv6 + 1
	uint16_t port;							 // Porta para desconverter de big endian para little endian (disposivo)

	// Se for ipv4
	if (addr->sa_family == AF_INET)
	{
		version = 4;
		struct sockaddr_in *addr4 = (struct sockaddr_in *)addr; // cast para mudar o tipo do ponteiro e conseguir acessar os campos
		// Tenta converter da representação de rede para a representação textual
		if (!inet_ntop(AF_INET, &(addr4->sin_addr), addrstr,
					   INET6_ADDRSTRLEN + 1))
		{
			logexit("ntop");
		}
		// Converte da representação de rede para a representação do dispositivo
		port = ntohs(addr4->sin_port); // network to host short
	}
	// Se for ipv6 é a mesma logica
	else if (addr->sa_family == AF_INET6)
	{
		version = 6;
		struct sockaddr_in6 *addr6 = (struct sockaddr_in6 *)addr;
		if (!inet_ntop(AF_INET6, &(addr6->sin6_addr), addrstr,
					   INET6_ADDRSTRLEN + 1))
		{
			logexit("ntop");
		}
		port = ntohs(addr6->sin6_port); // network to host short
	}
	// Se não for nada cai fora
	else
	{
		logexit("unknown protocol family.");
	}

	// Se chegou aqui é porque deu bom, printa tipo do ip, endereço e a porta
	if (str)
	{
		snprintf(str, strsize, "IPv%d %s %hu", version, addrstr, port);
	}
}

// Inicializa o storage corretamente
int server_sockaddr_init(const char *proto, const char *portstr,
						 struct sockaddr_storage *storage)
{
	// Faz o parse da porta
	uint16_t port = (uint16_t)atoi(portstr); // unsigned short
	if (port == 0)
	{
		return -1;
	}
	port = htons(port); // host to network short

	// Inicializar o storage
	memset(storage, 0, sizeof(*storage));
	// Verifica o protocolo (v4 ou v6) e trata corretamente
	if (0 == strcmp(proto, "v4"))
	{
		struct sockaddr_in *addr4 = (struct sockaddr_in *)storage;
		addr4->sin_family = AF_INET;
		addr4->sin_addr.s_addr = INADDR_ANY; // isso faz com o que o servidor possa rodar em todos os endereços do computador
		addr4->sin_port = port;
		return 0;
	}
	else if (0 == strcmp(proto, "v6"))
	{
		struct sockaddr_in6 *addr6 = (struct sockaddr_in6 *)storage;
		addr6->sin6_family = AF_INET6;
		addr6->sin6_addr = in6addr_any; // isso faz com o que o servidor possa rodar em todos os endereços do computador
		addr6->sin6_port = port;
		return 0;
	}
	else
	{
		return -1;
	}
}
