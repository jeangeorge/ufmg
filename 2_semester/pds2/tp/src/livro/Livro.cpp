#include "../../include/livro/Livro.hpp"

Livro::Livro(int id, string titulo, string autor, string genero,
		int quantidadeDeCopias) : id(id), titulo(titulo), autor(autor),
		genero(genero), quantidadeDeCopias(quantidadeDeCopias) {}

string Livro::toString() {
	stringstream ss;
	ss << this->id << "\t- " << this->titulo << "\t- " << this->autor << "\t- "
	   << this->genero << "\t- " << this->quantidadeDeCopias;
	return ss.str();
}

string Livro::toStringToSave() {
	stringstream ss;
	ss << this->id << ";" << this->titulo << ";" << this->autor << ";"
	   << this->genero << ";" << this->quantidadeDeCopias << "\n";
	return ss.str();
}

/*/void Livro::aumentarQuantidade();
 string toString();/*/

string Livro::getAutor() {
	return this->autor;
}

void Livro::setAutor(string autor) {
	this->autor = autor;
}

string Livro::getGenero() {
	return this->genero;
}

void Livro::setGenero(string genero) {
	this->genero = genero;
}

int Livro::getId() {
	return this->id;
}

void Livro::setId(int id) {
	this->id = id;
}

int Livro::getQuantidadeDeCopias() {
	return this->quantidadeDeCopias;
}

void Livro::setQuantidadeDeCopias(int quantidadeDeCopias) {
	this->quantidadeDeCopias = quantidadeDeCopias;
}

string Livro::getTitulo() {
	return this->titulo;
}

void Livro::setTitulo(string titulo) {
	this->titulo = titulo;
}
