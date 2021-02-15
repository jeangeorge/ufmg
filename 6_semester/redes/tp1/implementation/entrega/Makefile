all:
	g++ -Wall -c console.cpp
	gcc -Wall -c common.c
	g++ -Wall cliente.cpp console.o common.o -lpthread  -o cliente
	gcc -Wall servidor.c common.o -lpthread -o servidor

clean:
	rm common.o console.o cliente servidor
