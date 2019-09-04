#include "Cubo.hpp"

#include <iostream>

using namespace std;

Cubo::Cubo(double lado){
	this->lado = lado;
}

void Cubo::imprime(){
	cout << "Cubo(" << this->centroX << "," << this->centroY << "," << this->centroZ << ")" << endl;
}

double Cubo::getArea(){
	return(6*(this->lado * this->lado));
}

double Cubo::getVolume(){
	return(this->lado * this->lado * this->lado);
}
