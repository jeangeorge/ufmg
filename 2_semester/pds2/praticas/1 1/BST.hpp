#ifndef BST_H
#define BST_H

#include <iostream>

using namespace std;

/*Defino as estruturas No e Arvore*/

struct No {
	int dado;
	No* esq;
	No* dir;
};

struct Arvore {
	No* raiz = nullptr;
	void inserirNo(int data);
	void removerNo(int data);
	void mostrar();
};

#endif
