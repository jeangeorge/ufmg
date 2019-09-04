#include "FormaTridimensional.hpp"

#ifndef CUBO_H
#define CUBO_H

class Cubo : public FormaTridimensional{
	private:
		double lado;

	public:
		Cubo(double lado);
		void imprime() override;
		double getArea() override;
		double getVolume() override;
};

#endif
