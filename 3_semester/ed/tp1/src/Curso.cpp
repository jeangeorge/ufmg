#include "Curso.hpp"
#include <sstream>

Curso::Curso(int id, const string& nome, int numVagas) : id(id), nome(nome), vagasDisponiveis(numVagas), sort(id) { }

Curso::Curso() : id(0), vagasDisponiveis(0), sort(0) {}

Curso::~Curso() {}

string Curso::toString() {
	std::stringstream ss;
	ss << nome << " " << vagasDisponiveis;
	return ss.str();
}
