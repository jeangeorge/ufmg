#include "FormaBidimensional.hpp"

#ifndef QUADRADO_H
#define QUADRADO_H

class Quadrado : public FormaBidimensional{
	private:
		double lado;

	public:
		Quadrado(double x, double y, double lado);
		void imprime() override;
		double getArea() override;
};

#endif
