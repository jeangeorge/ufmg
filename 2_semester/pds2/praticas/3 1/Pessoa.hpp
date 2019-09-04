using namespace std;

#ifndef PESSOA_H
#define PESSOA_H

#include <string>

class Pessoa{
	private:
		string nome, endereco;
	public:
		Pessoa(string nome, string endereco);

		string getEndereco();
		void setEndereco(string endereco);

		string getNome();
		void setNome(string nome);

		void imprimeInformacoes();
};

#endif
