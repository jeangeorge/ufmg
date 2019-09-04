#include "Medusa.hpp"

Medusa::Medusa() : Criatura("Medusa",3,8) {}

int Medusa::atacar() {
  int ataquePts = 0;

  ataquePts += dadoAtaque1.rolar();
  ataquePts += dadoAtaque2.rolar();

  if (ataquePts == 12) {
    ataquePts = 1000;
  }

  return ataquePts;
}

int Medusa::defender() {
  int defesaPts = 0;

  defesaPts += dadoDefesa.rolar();

  return defesaPts;
}

Medusa::~Medusa() {}
