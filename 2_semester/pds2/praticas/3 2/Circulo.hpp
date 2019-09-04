#include "FormaBidimensional.hpp"

#ifndef CIRCULO_H
#define CIRCULO_H

class Circulo : public FormaBidimensional{
	private:
		double raio;

	public:
		Circulo(double raio,double x, double y);
		void imprime() override;
		double getArea() override;
};

#endif
