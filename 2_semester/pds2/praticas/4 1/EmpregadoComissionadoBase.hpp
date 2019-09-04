#ifndef BASE_H
#define BASE_H

#include <iostream>
using std::cout;

#include "EmpregadoComissionado.hpp"

class EmpregadoComissionadoBase : public EmpregadoComissionado {
 public:
  EmpregadoComissionadoBase(const string &, const string &, const string &, int, int, int, double = 0.0, double = 0.0, double = 0.0);

  double getSalarioBase() const;
  void setSalarioBase(double);

  virtual double salario() const;
  void imprime() const override;

 private:
  double salarioBase;
};

#endif
