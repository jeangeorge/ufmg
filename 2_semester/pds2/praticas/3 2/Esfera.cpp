#include "Esfera.hpp"

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

Esfera::Esfera(double raio, double x, double y, double z) : FormaTridimensional(x,y,z), raio(raio) {}
Esfera::Esfera(double raio, double x, double y) : FormaTridimensional(x,y,0), raio(raio) {}
Esfera::Esfera(double raio, double x) : FormaTridimensional(x,0,0), raio(raio) {}
Esfera::Esfera(double raio) : FormaTridimensional(0,0,0), raio(raio) {}
Esfera::Esfera() : FormaTridimensional(0,0,0), raio(0) {}

void Esfera::imprime(){
	cout << "Esfera(" << this->centroX << "," << this->centroY << "," << this->centroZ << ")" << endl;
}

double Esfera::getArea(){
	return(4 * M_PI * pow(this->raio,2));
}

double Esfera::getVolume(){
	return((4.0/3) * M_PI * pow(this->raio,3));
}
