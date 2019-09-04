using namespace std;

#ifndef ESTUDANTE_H
#define ESTUDANTE_H

#include <vector>
#include "Pessoa.hpp"

class Estudante : public Pessoa{
	private:
		vector<pair<string,int>> cursosENotas;

	public:
		Estudante(string nome, string endereco);

		void adicionarCursoNota(string curso, int nota);
		int* getNotas();
		vector<string> getCursos();
		double getNotaMedia();
		void imprimirNotas();
};

#endif

