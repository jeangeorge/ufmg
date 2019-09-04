#include <iostream>

#ifndef TRIANGULO_H
#define TRIANGULO_H

class TrianguloInvalidoError : public std::exception {
 public:
  virtual const char* what() const throw () {
    return "TrianguloInvalidoError.";
  }
};

class Triangulo {
 public:
  Triangulo(double a, double b, double c);
  int determinarTipo();

 private:
  double a,b,c;
};

#endif
