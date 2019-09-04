#include "PacoteNoturno.hpp"

double PacoteNoturno::calcularCusto(){
	this->custoKG += this->taxaPorKG;
	return(this->peso * this->custoKG);
}

double PacoteNoturno::getTaxaNoturnaPorQuilo(){
	return this->taxaPorKG;
}

void PacoteNoturno::setTaxaNoturnaPorQuilo(double taxa){
	this->taxaPorKG = taxa;
}
