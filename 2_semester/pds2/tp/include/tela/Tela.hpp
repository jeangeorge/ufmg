#ifndef TELA_H
#define TELA_H

#include "Opcao.hpp"

#include <vector>

using std::vector;

class Tela {
	public:
		Tela();
		virtual ~Tela();

		void mostrar();
		virtual string getNomeTela() = 0;

	protected:
		string titulo;
		string cabecalho;
		vector<Opcao> opcoes;
};

#endif
