#ifndef JOGO_HPP
#define JOGO_HPP

#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Criatura.hpp"
#include "Barbaro.hpp"
#include "HomemAzul.hpp"
#include "Mago.hpp"
#include "Vampiro.hpp"
#include "Medusa.hpp"

using std::cout;
using std::endl;
using std::string;


class Jogo {
	public:
		Jogo();
		~Jogo();

		void jogar();
		void testaJogo();
		void turno(Criatura*, Criatura*);
		void imprimeVencedor();
		void desalocaCriaturas();

	private:
		Criatura* criatura1;
		Criatura* criatura2;
		Criatura* vencedor;
};

#endif
