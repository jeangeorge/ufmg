#include "Barbaro.hpp"

Barbaro::Barbaro() : Criatura("Barbaro",0,12) { }

Barbaro::~Barbaro() {}

int Barbaro::atacar() {
  int ataquePts = 0;

  ataquePts += dadoAtaque1.rolar();
  ataquePts += dadoAtaque2.rolar();

  return ataquePts;
}

int Barbaro::defender() {
  double defesaPts = 0;

  defesaPts += dadoDefesa1.rolar();
  defesaPts += dadoDefesa2.rolar();

  return defesaPts;
}
