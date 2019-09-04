#ifndef USUARIO_H
#define USUARIO_H

#include "Pessoa.hpp"

#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::string;

class Usuario : public Pessoa {
	public:
		Usuario(int id, string nome, string sobrenome, string cpf, char sexo,
				string dataNascimento, string email, string telefone, bool status);
		~Usuario();

		string toString() override;
		string toStringToSave() override;

		string getEmail();
		void setEmail(string email);

		bool getStatus();
		void setStatus(bool status);

		string getTelefone();
		void setTelefone(string telefone);
		void setDiasBloqueados(int);
		int getDiasBloqueados();

		static bool getCpfValido(string& cpf, bool bloquearEntradaVazia);
		static bool getSexoValido(string& sexo);
		static bool getStatusValido(string& status);

	private:
		string email, telefone;
		bool status;
		int diasBloqueados;

		int gerarID() override;
};

#endif
