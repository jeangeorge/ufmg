#ifndef TELA_LIVROS_H
#define TELA_LIVROS_H

#include "Tela.hpp"

class TelaLivros : public Tela {
	public:
		TelaLivros();
		string getNomeTela() override;
};

#endif
