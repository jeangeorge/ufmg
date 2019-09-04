#include "Pessoa.hpp"
#include <iostream>

Pessoa::Pessoa(string nome, string endereco){
	this->nome = nome;
	this->endereco = endereco;
}

string Pessoa::getEndereco() {
	return this->endereco;
}
void Pessoa::setEndereco(string endereco) {
	this->endereco = endereco;
}

string Pessoa::getNome() {
	return this->nome;
}
void Pessoa::setNome(string nome) {
	this->nome = nome;
}

void Pessoa::imprimeInformacoes(){
	cout << this->nome << ":" << this->endereco << endl;
}
