#include <cmath>

#include "Circunferencia.hpp"

bool Circunferencia::verificaIntersecao(Circunferencia c){
	int distancia = pow((centro.x - c.centro.x),2) + pow((centro.y - c.centro.y),2);
	int somaRaios = pow((raio + c.raio),2);
	if(distancia < somaRaios)
		return true;
	else
		return false;
}
