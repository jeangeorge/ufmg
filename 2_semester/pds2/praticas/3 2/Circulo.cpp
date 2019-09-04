#include "Circulo.hpp"

#include <iostream>
#include <cmath>

using namespace std;

Circulo::Circulo(double raio,double x, double y) : FormaBidimensional(x,y),raio(raio) {}

void Circulo::imprime(){
	cout << "Circulo(" << this->centroX << "," << this->centroY << ")" << endl;
}

double Circulo::getArea(){
	return(M_PI * this->raio * this->raio);
}
