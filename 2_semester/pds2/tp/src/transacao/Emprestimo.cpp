#include "../../include/transacao/Emprestimo.hpp"

Emprestimo::Emprestimo(int idEmprestimo, int idLivro, int idUsuario,
		int diaRealizacao, int mesRealizacao, int anoRealizacao, int valorMulta) : 
		idEmprestimo(idEmprestimo),	idLivro(idLivro), idUsuario(idUsuario), diaRealizacao(diaRealizacao),
		mesRealizacao(mesRealizacao), anoRealizacao(anoRealizacao), valorMulta(valorMulta) {
	criarDataDevolucao();

}

Emprestimo::~Emprestimo() {
}

string Emprestimo::toString() {
	stringstream ss;
	ss << this->idEmprestimo << "\t- " << this->idLivro << "\t- " << this->idUsuario
			<< "\t- " << this->diaRealizacao << "\t- " << this->mesRealizacao << "\t- " << this->anoRealizacao
			<< "\t- " << this->diaDevolucao << "\t- " << this->mesDevolucao << "\t- " << this->anoDevolucao
			<< "\t- " << this->valorMulta;
	return ss.str();
}

string Emprestimo::toStringToSave() {
	stringstream ss;
	ss << this->idEmprestimo << ";" << this->idLivro << ";" << this->idUsuario
			<< ";" << this->diaRealizacao << ";" << this->mesRealizacao << ";" << this->anoRealizacao
			<< ";" << this->diaDevolucao << ";" << this->mesDevolucao << ";" << this->anoDevolucao
			<< ";" << this->valorMulta << "\n";
	return ss.str();
}

/*
const string& Emprestimo::getDataDevolucao() const {
	return this->dataDevolucao;
}

void Emprestimo::setDataDevolucao(const string& dataDevolucao) {
	this->dataDevolucao = dataDevolucao;
}
*/

void Emprestimo::criarDataDevolucao() {
	this->diaDevolucao = this->diaRealizacao + 7;
	if(this->diaDevolucao > 31) {
		this->mesDevolucao = this->mesRealizacao + 1;
		if(this->mesDevolucao > 12){
				this->anoDevolucao = this->anoRealizacao + 1;
				this->mesDevolucao = 1;
		}
	} else {
		this->mesDevolucao = this->mesRealizacao;
		this->anoDevolucao = this->anoRealizacao;
	}
}

int Emprestimo::getIdEmprestimo() {
	return this->idEmprestimo;
}

void Emprestimo::setIdEmprestimo(int idEmprestimo) {
	this->idEmprestimo = idEmprestimo;
}

int Emprestimo::getIdLivro() {
	return this->idLivro;
}

void Emprestimo::setIdLivro(int idLivro) {
	this->idLivro = idLivro;
}

int Emprestimo::getIdUsuario() {
	return this->idUsuario;
}

void Emprestimo::setIdUsuario(int idUsuario) {
	this->idUsuario = idUsuario;
}

int Emprestimo::getValorMulta() {
	return this->valorMulta;
}

void Emprestimo::setValorMulta(int valorMulta) {
	this->valorMulta = valorMulta;
}

int Emprestimo::getDiaDevolucao() {
	return this->diaDevolucao;
}

int Emprestimo::getMesDevolucao() {
	return this->mesDevolucao;
}

int Emprestimo::getAnoDevolucao() {
	return this->anoDevolucao;
}

void Emprestimo::setDiaRealizacao(int dia){
	this->diaRealizacao = dia;
}

void Emprestimo::setMesRealizacao(int mes){
	this->mesRealizacao = mes;
}

void Emprestimo::setAnoRealizacao(int ano){
	this->anoRealizacao = ano;
}

void Emprestimo::setDiaDevolucao(int dia){
	this->diaDevolucao = dia;
}

void Emprestimo::setMesDevolucao(int mes){
	this->mesDevolucao = mes;
}

void Emprestimo::setAnoDevolucao(int ano){
	this->anoDevolucao = ano;
}
