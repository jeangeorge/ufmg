#include "Candidato.hpp"
#include <sstream>

Candidato::Candidato(int id, const string& nome, double nota, int opcao1, int opcao2) : id(id), nome(nome), nota(nota), opcao1(opcao1), opcao2(opcao2) {
	std::stringstream ss;
	ss << nota;
	sort = ss.str();
	aprovado = false;
}

Candidato::Candidato() {
	id = 0;
	nome = "";
	nota = 0;
	opcao1 = 0;
	opcao2 = 0;
	sort = "";
	aprovado = false;
}

string Candidato::toString() {
	std::stringstream ss;
	ss << nota << " " << opcao1 << " " << opcao2;
	return ss.str();
}
