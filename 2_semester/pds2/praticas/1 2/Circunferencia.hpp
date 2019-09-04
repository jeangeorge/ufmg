#ifndef CIRCUNFERENCIA_H
#define CIRCUNFERENCIA_H

#include <iostream>

using namespace std;

// Defino as estruturas Ponto e Circunferencia
struct Ponto{
	int x;
	int y;
};

struct Circunferencia {
	int id;
	Ponto centro;
	int raio;

	bool verificaIntersecao(Circunferencia circunferencia);
};

#endif
