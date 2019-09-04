#ifndef AQUECEDOR_H
#define AQUECEDOR_H

class Aquecedor{
	public:
		double temperatura;

        Aquecedor();
        Aquecedor(double);

        void aquecer();
        void aquecer(double valor);

        void resfriar();
        void resfriar(double valor);

        double getTemperatura();
};

#endif
