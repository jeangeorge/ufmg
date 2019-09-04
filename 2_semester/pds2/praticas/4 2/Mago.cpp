#include "Mago.hpp"

Mago::Mago() : Criatura("Mago",0,10) {
  vidas = QUANTIDADE_INICIAL_VIDAS;
}

Mago::~Mago() {}

void Mago::setForca(int novaForca) {
  forca = novaForca;

  if (vidas == QUANTIDADE_INICIAL_VIDAS && forca < Criatura::FORCA_MINIMA) {
    vidas--;
    Criatura::setForca(20);
    cout << "Mago revive" << endl;
  }
}

int Mago::atacar() {
  int atacarPts = 0;

  atacarPts += dadoAtaque1.rolar();
  atacarPts += dadoAtaque2.rolar();

  return atacarPts;
}

int Mago::defender() {
  int defesaPts = 0;

  defesaPts += dadoDefesa1.rolar();
  defesaPts += dadoDefesa2.rolar();

  return defesaPts;
}
