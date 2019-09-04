#include "EmpregadoComissionado.hpp"

EmpregadoComissionado::EmpregadoComissionado(const string& primeiro,
                                             const string& ultimo,
                                             const string& cpf, int mes,
                                             int dia, int ano, double vendas,
                                             double taxa)
    : Empregado(primeiro, ultimo, cpf, mes, dia, ano) {
  setVendasBrutas(vendas);
  setTaxaComissao(taxa);
}

void EmpregadoComissionado::setTaxaComissao(double taxa) {
  taxaComissao = ((taxa > 0.0 && taxa < 1.0) ? taxa : 0.0);
}

void EmpregadoComissionado::setVendasBrutas(double vendas) {
  vendasBrutas = ((vendas < 0.0) ? 0.0 : vendas);
}

double EmpregadoComissionado::getTaxaComissao() const { return taxaComissao; }

double EmpregadoComissionado::getVendasBrutas() const { return vendasBrutas; }

double EmpregadoComissionado::salario() const{
  return getTaxaComissao() * getVendasBrutas();
}

void EmpregadoComissionado::imprime() const {
  cout << "empregado comissionado: ";
  Empregado::imprime();
  cout << "\nvendas brutas: " << getVendasBrutas()
       << "; taxa comissao: " << getTaxaComissao();
}
