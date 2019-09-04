#include <iostream>

#include "Triangulo.hpp"

using namespace std;

int main() {
  try {
    Triangulo t(1,2,3);
    cout << t.determinarTipo() << endl;
  } catch (TrianguloInvalidoError& e) {
    std::cout << "Erro: " << e.what() << std::endl;
  }
}
