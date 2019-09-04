#ifndef BIBLIOTECARIO_H
#define BIBLIOTECARIO_H

#include "Pessoa.hpp"
#include "../livro/Livro.hpp"

#include <iostream>
#include <fstream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::ifstream;
using std::ios_base;
using std::istringstream;
using std::vector;

class Bibliotecario : public Pessoa {
	public:
		Bibliotecario();
		Bibliotecario(int id, string login, string senha, string nome,
				string sobrenome, string cpf, char sexo, string dataNascimento);
		~Bibliotecario();

		bool logarNoSistema(const vector<Bibliotecario>& bibliotecariosCadastrados);

		string toString() override;
		string toStringToSave() override;

	private:
		string login, senha;

		bool receberEntradas(string& inputLogin, string& inputSenha);
		bool validarEntradasLogin(
				const vector<Bibliotecario>& bibliotecariosCadastrados,
				string inputLogin, string inputSenha);
		int gerarID() override;
};

#endif
