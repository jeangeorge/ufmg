#include <iostream>
#include <vector>
#include <typeinfo>
#include "Forma.hpp"
#include "FormaBidimensional.hpp"
#include "FormaTridimensional.hpp"
#include "Circulo.hpp"
#include "Quadrado.hpp"
#include "Esfera.hpp"
#include "Cubo.hpp"

using std::cout;
using std::endl;
using std::vector;

int main()
{
  vector<Forma*> formas(4);
  formas[0] = new Circulo(3.5, 6, 9);
  formas[1] = new Quadrado(12, 2, 2);
  formas[2] = new Esfera(5, 1.5, 4.5);
  formas[3] = new Cubo(2.2);

  for ( int i = 0; i < 4; i++ )
  {
    formas[i]->imprime();
    // downcast, se Forma eh uma FormaBidimensional, exibe a area
    FormaBidimensional *biDimPtr = dynamic_cast<FormaBidimensional*>(formas[i]);
    if ( biDimPtr != 0 )
    {
      cout << biDimPtr->getArea() << endl;
    }
    // downcast, se Forma eh uma FormaTridimensional, exibe a area e o volume
    FormaTridimensional *triDimPtr = dynamic_cast<FormaTridimensional*>(formas[i]);
    if ( triDimPtr != 0 )
    {
      cout << triDimPtr->getArea() << endl;
      cout << triDimPtr->getVolume() << endl;
    }
  }

  return 0;
}
