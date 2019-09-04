#include "../../include/pessoa/Pessoa.hpp"

Pessoa::Pessoa() {}

Pessoa::Pessoa(int id, string nome, string sobrenome, string cpf, char sexo,
		string dataNascimento) : id(id),	nome(nome),	sobrenome(sobrenome),
		cpf(cpf), sexo(sexo), dataNascimento(dataNascimento) {}

int Pessoa::getId() {
	return this->id;
}

string Pessoa::getDataNascimento() {
	return this->dataNascimento;
}

void Pessoa::setDataNascimento(string dataNascimento) {
	this->dataNascimento = dataNascimento;
}

string Pessoa::getNome() {
	return this->nome;
}

void Pessoa::setNome(string nome) {
	this->nome = nome;
}

char Pessoa::getSexo() {
	return this->sexo;
}

void Pessoa::setSexo(char sexo) {
	this->sexo = sexo;
}

string Pessoa::getSobrenome() {
	return this->sobrenome;
}

void Pessoa::setSobrenome(string sobrenome) {
	this->sobrenome = sobrenome;
}

string Pessoa::getCpf() {
	return this->cpf;
}

void Pessoa::setCpf(string cpf) {
	this->cpf = cpf;
}

Pessoa::~Pessoa() {
}

int Pessoa::gerarID() {
	return 0;
}

string Pessoa::toString() {
	std::stringstream ss;
	ss << this->nome << "\t- " << this->sobrenome << "\t- " << this->cpf << "\t- "
			<< this->sexo << "\t- " << this->dataNascimento;
	return ss.str();
}

string Pessoa::toStringToSave() {
	std::stringstream ss;
	ss << this->nome << ";" << this->sobrenome << ";" << this->cpf << ";"
			<< this->sexo << ";" << this->dataNascimento;
	return ss.str();
}
