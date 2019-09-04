#include <iostream>
#include <sstream>
#include <string>

#include "BST.hpp"

using namespace std;

int main(int argc, char** argv){
	Arvore* arvore = new Arvore; // Minha struct arvore
	int valor;

	while(cin >> valor){
		arvore->inserirNo(valor);
	}

	arvore->mostrar();

	delete(arvore);

	return 0;
}
