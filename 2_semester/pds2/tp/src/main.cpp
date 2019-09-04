#include <iostream>

#include "../include/biblioteca/Biblioteca.hpp"

int main() {

	Biblioteca *biblioteca = new Biblioteca("Biblioteca Central da Universidade Federal de Minas Gerais",
	                                        "Av. Pres. Antonio Carlos, 6627 - Pampulha, Belo Horizonte",
	                                       "(31) 3409-4617");

	delete biblioteca;

	return 0;
}
