#ifndef MAGO_HPP
#define MAGO_HPP

#include <iostream>

#include "Criatura.hpp"

using std::string;
using std::cout;
using std::endl;

class Mago : public Criatura {
 public:
 		static const int QUANTIDADE_INICIAL_VIDAS = 2;

 		Mago();
 		~Mago();

 		void setForca(int);

 		int atacar() override;
 		int defender() override;

 	private:
 		Dado dadoAtaque1;
 		Dado dadoAtaque2;
 		Dado dadoDefesa1;
 		Dado dadoDefesa2;
 		int vidas;
};

#endif
