#ifndef COMISSIONADO_H
#define COMISSIONADO_H

#include <iostream>

#include "Empregado.hpp"

using std::cout;

class EmpregadoComissionado : public Empregado {
 public:
  EmpregadoComissionado(const string&, const string&, const string&, int, int,
                        int, double = 0.0, double = 0.0);

  double getTaxaComissao() const;
  void setTaxaComissao(double);

  double getVendasBrutas() const;
  void setVendasBrutas(double);

  virtual double salario() const;
  void imprime() const override;

 private:
  double taxaComissao;
  double vendasBrutas;
};

#endif
