#ifndef MEDUSA_HPP
#define MEDUSA_HPP

#include "Criatura.hpp"

class Medusa : public Criatura {
 public:
	static const int OLHAR_DA_MEDUSA = 1000;

  Medusa();
  ~Medusa();

  int atacar() override;
  int defender() override;

 private:
  Dado dadoAtaque1;
  Dado dadoAtaque2;
  Dado dadoDefesa;
};

#endif
