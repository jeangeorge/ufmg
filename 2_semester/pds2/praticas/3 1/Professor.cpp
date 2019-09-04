#include "Professor.hpp"

Professor::Professor(string nome, string endereco) : Pessoa(nome,endereco){ }

vector<string> Professor::getCursos(){
	return (this->cursosLecionados);
}

bool Professor::adicionarCurso(string curso){
	for(unsigned int i=0;i<this->cursosLecionados.size();i++){
		if(curso == this->cursosLecionados[i]){
			return false;
		}
	}

	this->cursosLecionados.push_back(curso);
	return true;
}

bool Professor::removerCurso(string curso){
	for(unsigned int i=0;i<this->cursosLecionados.size();i++){
		if(curso == this->cursosLecionados[i]){
			this->cursosLecionados.erase(this->cursosLecionados.begin() + i);
			return true;
		}
	}

	return false;
}
