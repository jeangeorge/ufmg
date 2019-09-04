#include "Pacote.hpp"

#ifndef PACOTE_NOTURNO_H
#define PACOTE_NOTURNO_H

class PacoteNoturno : public Pacote {
	private:
		double taxaPorKG;

	public:
		PacoteNoturno(string nomeDestinatario, string enderecoDestinatario, string cidadeDestinatario, string estadoDestinatario, int cepDestinatario, string  nomeRemetente, string  enderecoRemetente, string  cidadeRemetente, string  estadoRemetente, int cepRemetente, double peso, double custoKG, double taxa) : Pacote(nomeDestinatario, enderecoDestinatario, cidadeDestinatario, estadoDestinatario, cepDestinatario, nomeRemetente, enderecoRemetente, cidadeRemetente, estadoRemetente, cepRemetente, peso, custoKG), taxaPorKG(taxa) {}

		double calcularCusto() override;

		double getTaxaNoturnaPorQuilo();
		void setTaxaNoturnaPorQuilo(double taxa);
};

#endif
