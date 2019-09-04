#include "PacoteDoisDias.hpp"

double PacoteDoisDias::calcularCusto(){
	return(Pacote::calcularCusto() + this->taxaFixa);
}

double PacoteDoisDias::getTaxaFixa(){
	return(this->taxaFixa);
}

void PacoteDoisDias::setTaxaFixa(double taxaFixa){
	this->taxaFixa = taxaFixa < 0 ? 0 : taxaFixa;
}
