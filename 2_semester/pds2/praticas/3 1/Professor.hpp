#ifndef PROFESSOR_H
#define PROFESSOR_H

#include <vector>
#include "Pessoa.hpp"

class Professor : public Pessoa{
	private:
		vector<string> cursosLecionados;

	public:
		Professor(string nome, string endereco);
		vector<string> getCursos();
		bool adicionarCurso(string curso);
		bool removerCurso(string curso);
};

#endif
