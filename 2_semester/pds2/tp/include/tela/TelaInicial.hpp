#ifndef TELA_INICIAL_H
#define TELA_INICIAL_H

#include "Tela.hpp"

class TelaInicial : public Tela {
  public:
    TelaInicial();
    string getNomeTela() override;
};

#endif
