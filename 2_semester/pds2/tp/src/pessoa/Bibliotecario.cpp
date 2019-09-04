#include "../../include/pessoa/Bibliotecario.hpp"
#include <conio.h>

Bibliotecario::Bibliotecario() : login(""), senha("") {}

Bibliotecario::Bibliotecario(int id, string login, string senha, string nome,
		string sobrenome, string cpf, char sexo, string dataNascimento) :
		Pessoa(id, nome, sobrenome, cpf, sexo, dataNascimento), login(login),
				senha(senha) {}

Bibliotecario::~Bibliotecario() {}

bool Bibliotecario::logarNoSistema(
		const vector<Bibliotecario>& bibliotecariosCadastrados) {
	// bool logado = false, sair = false;
	string inputLogin = "", inputSenha = "";

	cout << "TELA DE LOGIN" << endl;
	cout << "Digite seu login e senha abaixo Digite S (ou SAIR) para sair do Sistema." << endl;

	while (true) {
		if (!this->receberEntradas(inputLogin, inputSenha))
			return false;

		if (this->validarEntradasLogin(bibliotecariosCadastrados, inputLogin, inputSenha))
			return true;

		cout << "Usuario e/ou senha incorreto(s). Por favor tente novamente." << endl;
	}
}

string Bibliotecario::toString() {
	stringstream ss;
	ss << this->id << "\t- " << this->login << "\t- " << this->senha
			<< "\t- " << Pessoa::toString();
	return ss.str();
}

string Bibliotecario::toStringToSave() {
	stringstream ss;
	ss << this->id << ";" << this->login << ";" << this->senha << ";"
			<< Pessoa::toStringToSave() << "\n";
	return ss.str();
}

int Bibliotecario::gerarID() {
	return 0;
}

bool Bibliotecario::receberEntradas(string& inputLogin, string& inputSenha) {
	char c;

	cout << "\nLogin: ";
	cin >> inputLogin;
	if (inputLogin == "SAIR" || inputLogin == "S")
		return false;

	cout << "Senha: ";
	/*while ((c=_getch()) != '\n')
	{
	// put it onto the back of the password
	    inputSenha.push_back(c);
	// output a '*' character
	    _putch('*');
	}*/

	cin >> inputSenha;
	if (inputSenha == "SAIR" || inputSenha == "S")
		return false;

	return true;
}

// Faz a verificacao do input com os dados oriundos do arquivo
bool Bibliotecario::validarEntradasLogin(
		const vector<Bibliotecario>& bibliotecariosCadastrados,
		string inputLogin, string inputSenha) {
	for (auto bibliotecario : bibliotecariosCadastrados) {
		if (bibliotecario.login == inputLogin
				&& bibliotecario.senha == inputSenha) {
			this->id = bibliotecario.id;
			this->login = bibliotecario.login;
			this->senha = bibliotecario.senha;
			this->nome = bibliotecario.nome;
			this->sobrenome = bibliotecario.sobrenome;
			this->cpf = bibliotecario.cpf;
			this->sexo = bibliotecario.sexo;
			this->dataNascimento = bibliotecario.dataNascimento;
			return true;
		}
	}
	return false;
}
