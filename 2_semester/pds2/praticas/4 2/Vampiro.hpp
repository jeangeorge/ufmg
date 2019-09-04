#ifndef VAMPIRO_HPP
#define VAMPIRO_HPP

#include "Criatura.hpp"

class Vampiro : public Criatura {

 public:
  static const int CHARME_DO_VAMPIRO = 2000;

  Vampiro();

  int atacar() override;
  int defender() override;

 private:
  Dado dadoAtaque;
  Dado dadoDefesa;
};

#endif
