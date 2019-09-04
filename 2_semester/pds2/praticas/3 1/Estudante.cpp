#include <iostream>
#include "Estudante.hpp"

using namespace std;

Estudante::Estudante(string nome, string endereco) : Pessoa(nome,endereco) {}

void Estudante::adicionarCursoNota(string curso, int nota){
	cursosENotas.emplace_back(curso,nota);
}

int* Estudante::getNotas(){
	int* notas = nullptr;
	for(unsigned int i=0;i< this->cursosENotas.size(); i++){
		notas[i] = this->cursosENotas[i].second;
	}

	return notas;
}

vector<string> Estudante::getCursos(){
	vector<string> cursos;
	for(unsigned int i=0; i<this->cursosENotas.size(); i++){
		cursos.push_back(this->cursosENotas[i].first);
	}

	return cursos;
}

double Estudante::getNotaMedia(){
	int numeroDeNotas=0;
	double somaDasNotas = 0, mediaDasNotas;

	for(unsigned int i=0; i<this->cursosENotas.size(); i++){
		numeroDeNotas++;
		somaDasNotas += this->cursosENotas[i].second;
	}

	mediaDasNotas = somaDasNotas / numeroDeNotas;

	return mediaDasNotas;
}

void Estudante::imprimirNotas(){
	for(unsigned int i=0; i<this->cursosENotas.size(); i++){
		std::cout << this->cursosENotas[i].first << ":" <<this->cursosENotas[i].second << endl;
	}
}
