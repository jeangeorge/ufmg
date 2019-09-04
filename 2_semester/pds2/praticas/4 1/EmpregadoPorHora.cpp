#include "EmpregadoPorHora.hpp"

EmpregadoPorHora::EmpregadoPorHora(const string &primeiro, const string &ultimo,const string &cpf, int mes, int dia, int ano, double taxaHora, double horasTrabalhadas) : Empregado(primeiro, ultimo, cpf, mes, dia, ano){
  setTaxa(taxaHora);
  setHoras(horasTrabalhadas);
}

double EmpregadoPorHora::getHoras() const { return horas; }

void EmpregadoPorHora::setHoras(double horasTrabalhadas) {
  horas = (((horasTrabalhadas >= 0.0) && (horasTrabalhadas <= 168.0))
               ? horasTrabalhadas
               : 0.0);
}

double EmpregadoPorHora::getTaxa() const { return taxa; }

void EmpregadoPorHora::setTaxa(double taxaHora) {
  taxa = (taxaHora < 0.0 ? 0.0 : taxaHora);
}

double EmpregadoPorHora::salario() const {
  if (getHoras() <= 40) {
    return getTaxa() * getHoras();
  } else {
    return 40 * getTaxa() + ((getHoras() - 40) * getTaxa() * 1.5);
  }
}

void EmpregadoPorHora::imprime() const {
  cout << "hourly employee: ";
  Empregado::imprime();
  cout << "\ntaxa por hora: " << getTaxa()
       << "; horas trabalhadas: " << getHoras();
}
