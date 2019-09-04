#include "Pacote.hpp"

Pacote::Pacote(string nomeDestinatario, string enderecoDestinatario, string cidadeDestinatario, string estadoDestinatario, int cepDestinatario, string  nomeRemetente, string  enderecoRemetente, string  cidadeRemetente, string  estadoRemetente, int  cepRemetente, double peso, double custoKG){

	this->nomeRemetente = nomeRemetente;
	this->enderecoRemetente = enderecoRemetente;
	this->cidadeRemetente = cidadeRemetente;
	this->estadoRemetente = estadoRemetente;
	this->cepRemetente = cepRemetente;

	this->nomeDestinatario = nomeDestinatario;
	this->enderecoDestinatario = enderecoDestinatario;
	this->cidadeDestinatario = cidadeDestinatario;
	this->estadoDestinatario = estadoDestinatario;
	this->cepDestinatario = cepDestinatario;

	this->peso = peso < 0 ? 0 : peso;
	this->custoKG = custoKG < 0 ? 0 : custoKG;
}

Pacote::~Pacote(){

}

double Pacote::calcularCusto(){
	return(this->peso * this->custoKG);
}


int Pacote::getDestinatarioCEP() {
	return cepDestinatario;
}
void Pacote::setDestinatarioCEP(int cepDestinatario) {
	this->cepDestinatario = cepDestinatario;
}

int Pacote::getRemetenteCEP() {
	return cepRemetente;
}
void Pacote::setRemetenteCEP(int cepRemetente) {
	this->cepRemetente = cepRemetente;
}

string Pacote::getDestinatarioCidade() {
	return cidadeDestinatario;
}
void Pacote::setDestinatarioCidade(string cidadeDestinatario) {
	this->cidadeDestinatario = cidadeDestinatario;
}

string Pacote::getRemetenteCidade() {
	return cidadeRemetente;
}
void Pacote::setRemetenteCidade(string cidadeRemetente) {
	this->cidadeRemetente = cidadeRemetente;
}

double Pacote::getCustoKg() {
	return custoKG;
}
void Pacote::setCustoKg(double custoKg) {
	custoKG = custoKg;
}
string Pacote::getDestinatarioEndereco() {
	return enderecoDestinatario;
}
void Pacote::setDestinatarioEndereco(string enderecoDestinatario) {
	this->enderecoDestinatario = enderecoDestinatario;
}

string Pacote::getRemetenteEndereco() {
	return enderecoRemetente;
}
void Pacote::setRemetenteEndereco(string enderecoRemetente) {
	this->enderecoRemetente = enderecoRemetente;
}

string Pacote::getDestinatarioEstado() {
	return estadoDestinatario;
}
void Pacote::setDestinatarioEstado(string estadoDestinatario) {
	this->estadoDestinatario = estadoDestinatario;
}

string Pacote::getRemetenteEstado() {
	return estadoRemetente;
}
void Pacote::setRemetenteEstado(string estadoRemetente) {
	this->estadoRemetente = estadoRemetente;
}

string Pacote::getDestinatarioNome() {
	return nomeDestinatario;
}
void Pacote::setDestinatarioNome(string nomeDestinatario) {
	this->nomeDestinatario = nomeDestinatario;
}

string Pacote::getRemetenteNome() {
	return nomeRemetente;
}
void Pacote::setRemetenteNome(string nomeRemetente) {
	this->nomeRemetente = nomeRemetente;
}

double Pacote::getPeso() {
	return peso;
}
void Pacote::setPeso(double peso) {
	this->peso = peso < 0 ? 0 : peso;
}
