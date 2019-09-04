#ifndef SALARIADO_H
#define SALARIADO_H

#include "Empregado.hpp"

class EmpregadoSalariado : public Empregado
{

public:
  EmpregadoSalariado(const string&, const string&, const string&, int, int, int, double = 0.0);
  void setSalarioSemanal(double);
  double getSalarioSemanal() const;
  virtual double salario() const;
  virtual void imprime() const;

private:
  double salarioSemanal;

};

#endif
