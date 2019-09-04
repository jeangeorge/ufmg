#include "Curso.hpp"
#include "Candidato.hpp"
#include "Lista.hpp"
#include <typeinfo>
#include <iostream>
#include <algorithm>

using namespace std;

template <class T> Lista<T>::Lista() {
	primeiro = nullptr;
	ultimo = nullptr;
}

template <class T> Lista<T>::~Lista() {

}

template <class T> void Lista<T>::inserir(const T &dado) {
	if (primeiro == nullptr && ultimo == nullptr) {
		primeiro =  new No<T>();
		primeiro->dado = dado;
		ultimo = primeiro;
	} else {
		ultimo->proximo = new No<T>();
		ultimo->proximo->dado = dado;
		ultimo->proximo->proximo = nullptr;
		ultimo = ultimo->proximo;

	}
}

template <class T> void Lista<T>::ordenar() {
	No<T>* i =  new No<T>();
	// Ordenação decrescente
	for (i = this->primeiro; i->proximo != nullptr; i = i->proximo) {
		No<T>* j =  new No<T>();
		for (j = i->proximo; j != nullptr; j = j->proximo) {
			bool ordena = false;
			if (i->dado.sort < j->dado.sort) {
				ordena = true;
			} else if (i->dado.toString() == j->dado.toString()) {
				if (i->dado.id > j->dado.id) {
					ordena = true;
				}
			}
			// Caso seja necessário ordenar, faz a troca.
			if (ordena) {
				T temp = i->dado;
				i->dado = j->dado;
				j->dado = temp;
			}
		}
	}
}

template <class T> void Lista<T>::mostrar() {
	No<T>* aux =  new No<T>();
	aux = this->primeiro;
	while(aux) {
		cout << aux->dado.toString() << endl;
		aux = aux->proximo;
	}
}

template class Lista<Curso>;
template class Lista<Candidato>;
