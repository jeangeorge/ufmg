#ifndef FORMA_H
#define FORMA_H


class Forma{
	protected:
		double centroX, centroY;

	public:
		Forma(double x, double y);
		virtual ~Forma();

		virtual void imprime();
		virtual double getArea() = 0;
};

#endif
