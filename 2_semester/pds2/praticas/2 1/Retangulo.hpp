#ifndef RETANGULO_H
#define RETANGULO_H

#include <iostream>
#include "Ponto2D.hpp"

using namespace std;

class Retangulo{
	public:
		Ponto2D superiorEsq;
		Ponto2D inferiorDir;

		Retangulo(Ponto2D superiorEsq, Ponto2D inferiorDir);

		double calcularArea();

		double calcularIntersecao(Retangulo r);
};

#endif
