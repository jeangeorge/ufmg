#include "Quadrado.hpp"

#include <iostream>

using namespace std;

Quadrado::Quadrado(double lado, double x, double y) : FormaBidimensional(x,y), lado(lado) {}

void Quadrado::imprime(){
	cout << "Quadrado(" << this->centroX << "," << this->centroY << ")" << endl;
}

double Quadrado::getArea(){
	return(this->lado * this->lado);
}
