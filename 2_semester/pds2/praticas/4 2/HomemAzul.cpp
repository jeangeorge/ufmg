#include "HomemAzul.hpp"

HomemAzul::HomemAzul() : Criatura("Homem Azul",3,12) {
  dadoAtaque1 = Dado(10);
  dadoAtaque2 = Dado(10);
}

HomemAzul::~HomemAzul() {}

int HomemAzul::atacar() {
  int atacarPts = 0;

  atacarPts += dadoAtaque1.rolar();
  atacarPts += dadoAtaque2.rolar();

  return atacarPts;
}

int HomemAzul::defender() {
  int defesaPts = 0;

  if (forca > 0) {
    defesaPts += dadoDefesa1.rolar();
  }

  if (forca > 4) {
    defesaPts += dadoDefesa2.rolar();
  }

  if (forca > 8) {
    defesaPts += dadoDefesa3.rolar();
  }

  return defesaPts;
}
