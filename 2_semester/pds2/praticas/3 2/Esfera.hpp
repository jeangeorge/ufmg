#include "FormaTridimensional.hpp"

#ifndef ESFERA_H
#define ESFERA_H

class Esfera : public FormaTridimensional{
	private:
		double raio;

	public:
		Esfera(double raio, double x, double y, double z);
		Esfera(double raio, double x, double y);
		Esfera(double raio, double x);
		Esfera(double raio);
		Esfera();

		void imprime() override;
		double getArea() override;
		double getVolume();
};

#endif
