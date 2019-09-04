#ifndef PESSOA_H
#define PESSOA_H

#include <sstream>
#include <string>

using std::string;
using std::stringstream;

class Pessoa {
	public:
		Pessoa();
		Pessoa(int id, string nome, string sobrenome, string cpf, char sexo,
				string nascimento);
		virtual ~Pessoa();

		int getId();

		string getCpf();
		void setCpf(string cpf);

		string getDataNascimento();
		void setDataNascimento(string);

		string getNome();
		void setNome(string);

		string getSobrenome();
		void setSobrenome(string);

		char getSexo();
		void setSexo(char);

		virtual string toString();
		virtual string toStringToSave();

	protected:
		virtual int gerarID();
		static int getProximoId();

		int id;
		string nome, sobrenome, cpf, dataNascimento;
		char sexo;
};

#endif
