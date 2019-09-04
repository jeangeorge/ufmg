#ifndef OPCAO_H
#define OPCAO_H

#include <string>

using std::string;

class Opcao {
	public:
		Opcao(string valor, string opcao);

		string valor;
		string descricao;
};

#endif
