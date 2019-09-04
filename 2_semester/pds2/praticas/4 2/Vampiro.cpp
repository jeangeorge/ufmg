#include "Vampiro.hpp"

Vampiro::Vampiro() : Criatura("Vampiro",1,18) {
  dadoAtaque = Dado(12);
}

int Vampiro::atacar() {
  int atacarPts = 0;

  atacarPts += dadoAtaque.rolar();

  return atacarPts;
}

int Vampiro::defender() {
  int defesaPts = 0;

  int defesaResultado = dadoDefesa.rolar();
  defesaPts += defesaResultado;

  if (defesaResultado % 2 == 0) {
    defesaPts = CHARME_DO_VAMPIRO;
  }

  return defesaPts;
}
