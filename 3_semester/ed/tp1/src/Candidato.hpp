#ifndef CANDIDATO_H
#define CANDIDATO_H

#include <string>
using std::string;

class Candidato
{

public:
  Candidato(int, const string&, double, int, int);
  Candidato();
  string toString();
  int id;
  string nome;
  double nota;
  string sort;
  int opcao1, opcao2;
  bool aprovado;
};

#endif
