#ifndef EMPREGADO_H
#define EMPREGADO_H

#include <iostream>
#include <string>

#include "Data.hpp"

using std::string;

class Empregado {
 public:
  Empregado(const string&, const string&, const string&, int, int, int);
  virtual ~Empregado();

  Data getDataNascimento() const;
  void setDataNascimento(int, int, int);

  string getPrimeiroNome() const;
  void setPrimeiroNome(const string&);

  string getUltimoNome() const;
  void setUltimoNome(const string&);

  string getCPF() const;
  void setCPF(const string&);

  virtual double salario() const = 0;
  virtual void imprime() const;

 private:
  Data dataNascimento;
  string primeiroNome;
  string ultimoNome;
  string cpf;
};

#endif
