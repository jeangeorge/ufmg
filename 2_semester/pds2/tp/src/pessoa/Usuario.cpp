#include "../../include/pessoa/Usuario.hpp"

Usuario::Usuario(int id, string nome, string sobrenome, string cpf, char sexo,
		string dataNascimento, string email, string telefone, bool status) :
		Pessoa(id, nome, sobrenome, cpf, sexo, dataNascimento), email(email),
		telefone(telefone), status(status), diasBloqueados(0) {}

Usuario::~Usuario() {}

string Usuario::toString() {
	stringstream ss;
	ss << this->id << "\t- " << Pessoa::toString() << "\t- " << this->email << "\t- "
			<< this->telefone << "\t- " << this->status;
	return ss.str();
}

string Usuario::toStringToSave() {
	stringstream ss;
	ss << this->id << ";" << Pessoa::toStringToSave() << ";" << this->email << ";"
			<< this->telefone << ";" << this->status << "\n";
	return ss.str();
}

int Usuario::gerarID() {
	return 0;
}

void Usuario::setDiasBloqueados(int dias) {
    this->diasBloqueados = dias;
}

int Usuario::getDiasBloqueados() {
    return this->diasBloqueados;
}

string Usuario::getEmail() {
	return this->email;
}

void Usuario::setEmail(string email) {
	this->email = email;
}

bool Usuario::getStatus() {
	return this->status;
}

void Usuario::setStatus(bool status) {
	this->status = status;
}

string Usuario::getTelefone() {
	return this->telefone;
}

void Usuario::setTelefone(string telefone) {
	this->telefone = telefone;
}

bool Usuario::getCpfValido(string& cpf, bool bloquearEntradaVazia) {
	char* p = nullptr;
	while(true) {
		getline(cin, cpf);
		if(cpf == ":C")
			break;
		if(cpf.size() == 11 || (!bloquearEntradaVazia && cpf.empty())) {
			long converted = strtol(cpf.c_str(), &p, 10);
			if(*p == 0)
				return true;
		}
		cout << "CPF invalido. Digite um CPF valido ou ':C' para cancelar" << endl;
	}
	return false;
}

bool Usuario::getSexoValido(string& sexo) {
	while(true) {
		getline(cin, sexo);
		if(sexo == ":C")
			break;
		if(sexo == "M" || sexo == "F") {
			return true;
		}
		cout << "Sexo invalido. Digite apenas 'F' ou 'M', ou ':C' para cancelar" << endl;
	}
	return false;
}

bool Usuario::getStatusValido(string& status) {
	while(true) {
		getline(cin, status);
		if(status == ":C")
			break;
		if(status == "1" || status == "0") {
			return true;
		}
		cout << "Status invalido. Digite apenas '1' ou '0', ou ':C' para cancelar" << endl;
	}
	return false;
}
