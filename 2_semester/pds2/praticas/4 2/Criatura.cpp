#include "Criatura.hpp"

Criatura::Criatura(string nome, int armadura, int forca){
	this->nome = nome;
	this->armadura = armadura;
	this->forca = forca;
}

string Criatura::getNome() { return this->nome; }

void Criatura::setNome(string novoNome) { this->nome = novoNome; }

int Criatura::getArmadura() { return this->armadura; }

int Criatura::getForca() { return this->forca; }

void Criatura::setForca(int novaForca) { this->forca = novaForca; }

Criatura::~Criatura() {}
