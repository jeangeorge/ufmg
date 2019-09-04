#ifndef EMPREGADO_H
#define EMPREGADO_H

#include <iostream>
using std::cout;

#include <string>
using std::string;

#include "Data.hpp"

class Empregado
{

public:
  Empregado(const string&, const string&, const string&, int, int, int);
  void setPrimeiroNome(const string&);
  string getPrimeiroNome() const;
  void setUltimoNome(const string&);
  string getUltimoNome() const;
  void setCPF(const string&);
  string getCPF() const;
  void setDataNascimento(int, int, int);
  Data getDataNascimento() const;
  virtual double salario() const = 0;
  virtual void imprime() const;

private:
  string primeiroNome;
  string ultimoNome;
  string cpf;
  Data dataNascimento;

}; 

#endif