#ifndef CURSO_H
#define CURSO_H

#include <string>
#include "Lista.hpp"
#include "Candidato.hpp"

using std::string;

class Curso
{

public:
	Curso();
	Curso(int, const string&, int);
	~Curso();
	string toString();
	int id;
	string nome;
	int vagasDisponiveis;
	Lista<Candidato> aprovados, listaEspera;
	int sort;
};

#endif
