#ifndef PORHORA_H
#define PORHORA_H

#include <iostream>

#include "Empregado.hpp"

using std::cout;

class EmpregadoPorHora : public Empregado {
 public:
  EmpregadoPorHora(const string&, const string&, const string&, int, int, int,
                   double = 0.0, double = 0.0);

  double getHoras() const;
  void setHoras(double);

  double getTaxa() const;
  void setTaxa(double);

  virtual double salario() const;
  void imprime() const override;

 private:
  double horas;
  double taxa;
};

#endif
