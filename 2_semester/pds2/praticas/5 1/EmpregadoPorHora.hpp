#ifndef PORHORA_H
#define PORHORA_H

#include <iostream>
using std::cout;

#include "Empregado.hpp"

class EmpregadoPorHora : public Empregado
{

public:
  EmpregadoPorHora(const string&, const string&, const string&, int, int, int, double = 0.0, double = 0.0);
  void setTaxa(double);
  double getTaxa() const;
  void setHoras(double);
  double getHoras() const;
  virtual double salario() const;
  virtual void imprime() const;

private:
  double taxa;
  double horas;

}; 

#endif
