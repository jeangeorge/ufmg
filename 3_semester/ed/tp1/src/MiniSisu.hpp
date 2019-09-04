#ifndef MINISISU_H
#define MINISISU_H

#include "Lista.hpp"
#include "Curso.hpp"
#include "Candidato.hpp"

using std::string;

class MiniSisu
{

	public:
		MiniSisu();
		~MiniSisu();
		void preencherCursos(int);
		void preencherCandidatos(int);
		void alocarCandidatos();
		void mostrarResultado();
	private:
		Lista<Curso>* cursos;
		Lista<Candidato>* candidatos;
};

#endif
