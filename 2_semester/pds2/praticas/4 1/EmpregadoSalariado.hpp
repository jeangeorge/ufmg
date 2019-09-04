#ifndef SALARIADO_H
#define SALARIADO_H

#include "Empregado.hpp"

class EmpregadoSalariado : public Empregado {
 public:
  EmpregadoSalariado(const string&, const string&, const string&, int, int, int,
                     double = 0.0);

  double getSalarioSemanal() const;
  void setSalarioSemanal(double);

  virtual double salario() const;
  void imprime() const override;

 private:
  double salarioSemanal;
};

#endif
