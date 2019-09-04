#include "BST.hpp"

// Cria um no definindo suas ramificações a esquerda e direita como nulo
No* criarNo(int dado) {
	No* auxiliar = new No;
	auxiliar->dado = dado;
	auxiliar->esq = nullptr;
	auxiliar->dir = nullptr;
	return auxiliar;
}

// Recebe um no e um dado
// Como se trata de uma árvore de pesquisa, precisa verificar se o dado é menor ou maior do que o que presente no no
void inserirNoAuxiliar(No* no, int dado) {
	if (dado < no->dado) {
		if (no->esq == nullptr) {
			no->esq = criarNo(dado);
		} else {
			inserirNoAuxiliar(no->esq, dado);
		}
	} else if (dado > no->dado) {
		if (no->dir == nullptr) {
			no->dir = criarNo(dado);
		} else {
			inserirNoAuxiliar(no->dir, dado);
		}
	}
}

// Função para inserir um nó na arvore.
// Recebe um dado, caso a arvore não esteja vazia, chama uma função auxiliar de inserção, caso contrário simplesmente cria o no.
void Arvore::inserirNo(int dado) {
	if (raiz != nullptr) {
		inserirNoAuxiliar(raiz, dado);
	} else {
		raiz = criarNo(dado);
	}
}

// Ordenar que não ordena efetivamente mas mostra
void ordenar(No* no) {
	if(no == nullptr)
		return;

	ordenar(no->esq);
	cout << no->dado << " ";
	ordenar(no->dir);
}

// Mostrar que não mostra (?)
void Arvore::mostrar() {
	ordenar(raiz);
	cout << endl;
}
