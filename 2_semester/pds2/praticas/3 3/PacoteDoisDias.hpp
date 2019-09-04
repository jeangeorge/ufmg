#include "Pacote.hpp"

#ifndef PACOTE_2DIAS_H
#define PACOTE_2DIAS_H

class PacoteDoisDias : public Pacote {
	private:
		double taxaFixa;

	public:
		PacoteDoisDias(string nomeDestinatario, string enderecoDestinatario, string cidadeDestinatario, string estadoDestinatario, int cepDestinatario, string  nomeRemetente, string  enderecoRemetente, string  cidadeRemetente, string  estadoRemetente, int cepRemetente, double peso, double custoKG, double taxa) : Pacote(nomeDestinatario, enderecoDestinatario, cidadeDestinatario, estadoDestinatario, cepDestinatario, nomeRemetente, enderecoRemetente, cidadeRemetente, estadoRemetente, cepRemetente, peso, custoKG), taxaFixa(taxa) {}
		double calcularCusto() override;
		void setTaxaFixa(double taxaFixa);
		double getTaxaFixa();
};

#endif
