#ifndef DATA_H
#define DATA_H

#include <string>
#include <iostream>
using std::ostream;

class Data
{

friend ostream &operator<<(ostream &, const Data &);

public:
  Data(int m = 1, int d = 1, int a = 1900);
  void setData(int, int, int);
  Data &operator++(); // operador prefixo de incremento
  Data operator++(int); // operador posfixo de incremento
  const Data &operator+=(int); // adiciona dias
  bool anoBissexto(int) const; // ano bissexto?
  bool fimDoMes(int) const; // fim do mes?
  int getMes() const;

private:
  int mes;
  int dia;
  int ano;
  static const int dias[];
  void auxiliaIncremento(); // funcao auxiliar no incremento da data

};


#endif
