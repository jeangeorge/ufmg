#ifndef LISTA_H
#define LISTA_H

#include "No.hpp"

template <typename T> class Lista
{
	public:
		No<T> *primeiro, *ultimo;

		Lista();
		~Lista();

		void inserir(const T &dado);
		void ordenar();
		void mostrar();
};

#endif
