#include <iostream>

using std::cout;

#include "EmpregadoSalariado.hpp"

EmpregadoSalariado::EmpregadoSalariado(const string& primeiro,
                                       const string& ultimo, const string& cpf,
                                       int mes, int dia, int ano,
                                       double salario)
    : Empregado(primeiro, ultimo, cpf, mes, dia, ano) {
  setSalarioSemanal(salario);
}

void EmpregadoSalariado::setSalarioSemanal(double salario) {
  this->salarioSemanal = (salario < 0.0) ? 0.0 : salario;
}

double EmpregadoSalariado::getSalarioSemanal() const {
  return this->salarioSemanal;
}

double EmpregadoSalariado::salario() const { return getSalarioSemanal(); }

void EmpregadoSalariado::imprime() const {
  cout << "empregado salariado: ";
  Empregado::imprime();
  cout << "\nsalario semanal: " << getSalarioSemanal();
}
