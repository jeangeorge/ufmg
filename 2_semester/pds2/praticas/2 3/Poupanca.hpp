#ifndef AQUECEDOR_H
#define AQUECEDOR_H

class Poupanca{
	public:
        static double taxaDeJurosAnual;
        double saldoPoupanca;

        Poupanca();
        Poupanca(double);

        void calcularJurosMensal();
		void depositarValor(double valor);
        void sacarValor(double valor);
        static void setTaxaDeJurosAnual(double novaTaxa);
        double getSaldoPoupanca();
};

#endif
