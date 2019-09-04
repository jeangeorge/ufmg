#ifndef COMISSIONADO_H
#define COMISSIONADO_H

#include <iostream>
using std::cout;

#include "Empregado.hpp"

class EmpregadoComissionado : public Empregado
{

public:
  EmpregadoComissionado(const string&, const string&, const string&, int, int, 
    int, double = 0.0, double = 0.0);
  void setTaxaComissao(double);
  double getTaxaComissao() const;
  void setVendasBrutas(double);
  double getVendasBrutas() const; 
  virtual double salario() const;
  virtual void imprime() const;

private:
  double vendasBrutas;
  double taxaComissao;

};

#endif
