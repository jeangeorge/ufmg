#include "Forma.hpp"

#ifndef FORMA_TRIDIMENSIONAL
#define FORMA_TRIDIMENSIONAL

class FormaTridimensional : public Forma{
	protected:
		int centroZ;

	public:
		FormaTridimensional(double x, double y, double z) : Forma(x,y), centroZ(z) {}
		FormaTridimensional(double x, double y): Forma(x,y), centroZ(0) {}
		FormaTridimensional(double x): Forma(x,0), centroZ(0) {}
		FormaTridimensional() : Forma(0,0), centroZ(0) {}

		virtual double getVolume() = 0;
};

#endif

