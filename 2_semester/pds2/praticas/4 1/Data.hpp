#ifndef DATA_H
#define DATA_H

#include <iostream>

using std::ostream;

class Data {
 public:
  Data(int m = 1, int d = 1, int a = 1900);

  const Data &operator+=(int);  // adiciona dias

  int getMes() const;
  void setData(int, int, int);

  bool fimDoMes(int) const;     // fim do mes?
  bool anoBissexto(int) const;  // ano bissexto?

  Data &operator++();    // operador prefixo de incremento
  Data operator++(int);  // operador posfixo de incremento

 private:
  static const int dias[];
  int mes;
  int dia;
  int ano;

  void auxiliaIncremento();  // funcao auxiliar no incremento da data
  friend ostream &operator<<(ostream &, const Data &);
};

#endif
