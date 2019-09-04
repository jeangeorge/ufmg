#ifndef BARBARO_HPP
#define BARBARO_HPP

#include "Criatura.hpp"

class Barbaro : public Criatura {
 public:
  Barbaro();
  ~Barbaro();

  int atacar() override;
  int defender() override;

 private:
  Dado dadoAtaque1;
  Dado dadoAtaque2;
  Dado dadoDefesa1;
  Dado dadoDefesa2;
};

#endif
