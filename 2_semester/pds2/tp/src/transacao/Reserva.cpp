#include "../../include/transacao/Reserva.hpp"

Reserva::Reserva(int idReserva, int idUsuario, int idLivro) : 
		idReserva(idReserva), idLivro(idLivro), idUsuario(idUsuario) {}

Reserva::~Reserva() {}

string Reserva::toString() {
	stringstream ss;
	ss << this->idReserva << "\t- " << this->idUsuario << "\t- " << this->idLivro << ";";
	return ss.str();
}

string Reserva::toStringToSave() {
	stringstream ss;
	ss << this->idReserva << ";" << this->idUsuario << ";" << this->idLivro << "\n";
	return ss.str();
}

int Reserva::getIdReserva() {
	return this->idReserva;
}

void Reserva::setIdReserva(int idReserva) {
	this->idReserva = idReserva;
}

int Reserva::getIdLivro() {
	return this->idLivro;
}

void Reserva::setIdLivro(int idLivro) {
	this->idLivro = idLivro;
}

int Reserva::getIdUsuario() {
	return this->idUsuario;
}

void Reserva::setIdUsuario(int idUsuario) {
	this->idUsuario = idUsuario;
}

/*
string Reserva::getDataPrevista() {
	return this->dataPrevista;
}

void Reserva::setDataPrevista(string dataPrevista) {
	this->dataPrevista = dataPrevista;
}
*/