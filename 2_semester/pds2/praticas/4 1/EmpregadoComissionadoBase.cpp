#include "EmpregadoComissionadoBase.hpp"

EmpregadoComissionadoBase::EmpregadoComissionadoBase(
    const string &primeiro, const string &ultimo, const string &cpf, int mes,
    int dia, int ano, double vendas, double taxa, double salario)
    : EmpregadoComissionado(primeiro, ultimo, cpf, mes, dia, ano, vendas,
                            taxa) {
  setSalarioBase(salario);
}

double EmpregadoComissionadoBase::getSalarioBase() const {
	return salarioBase;
}

void EmpregadoComissionadoBase::setSalarioBase(double salario) {
  salarioBase = ((salario < 0.0) ? 0.0 : salario);
}

double EmpregadoComissionadoBase::salario() const {
  double sal = EmpregadoComissionado::salario();
  return getSalarioBase() + sal;
}

void EmpregadoComissionadoBase::imprime() const {
  cout << "Comissionado base ";
  EmpregadoComissionado::imprime();
  cout << "; salario base: " << getSalarioBase();
}
