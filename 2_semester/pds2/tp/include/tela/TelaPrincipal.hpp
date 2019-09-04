#ifndef TELA_PRINCIPAL_H
#define TELA_PRINCIPAL_H

#include "Tela.hpp"

class TelaPrincipal : public Tela {
	public:
		TelaPrincipal();
		string getNomeTela() override;
};

#endif
