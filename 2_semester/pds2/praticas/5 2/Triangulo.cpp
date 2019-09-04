#include "Triangulo.hpp"

Triangulo::Triangulo(double a, double b, double c) {
  if(a <= 0 || b <= 0 || c <= 0){
    std:: cout << "DALE";
    throw TrianguloInvalidoError();
  }

  if(!(abs(b - c) < a && a < b + c)){
    throw TrianguloInvalidoError();
  }

  if(!(abs(a - c) < b && b < a + c)){
    throw TrianguloInvalidoError();
  }

  if(!(abs(a - b) < c && c < a + b)){
    throw TrianguloInvalidoError();
  }

  this->a = a;
  this->b = b;
  this->c = c;
}

int Triangulo::determinarTipo(){
  if(a == b && a == c){
    return 1;
  }else if(a != b && a != c && b != c){
    return 3;
  }else{
    return 2;
  }
}
