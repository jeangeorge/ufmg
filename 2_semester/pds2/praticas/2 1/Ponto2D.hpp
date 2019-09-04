#ifndef PONTO2D_H
#define PONTO2D_H

#include <iostream>

using namespace std;

class Ponto2D{
	public:
		double x;
		double y;

		Ponto2D() : Ponto2D(0,0) {};

		Ponto2D(double x, double y);
};

#endif
