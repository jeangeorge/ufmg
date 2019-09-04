#include "../../include/tela/Tela.hpp"

#include <iostream>

using std::cout;
using std::endl;

Tela::Tela() {
	this->cabecalho = "\nPor favor selecione uma opcao valida:";
	this->opcoes.push_back(Opcao("S", "Sair do Sistema"));
}

Tela::~Tela() {}

void Tela::mostrar() {
	cout << endl << titulo;
	cout << this->cabecalho << endl;
	for (unsigned int i = 0; i < this->opcoes.size(); i++) {
		cout << this->opcoes[i].valor << " - " << this->opcoes[i].descricao << endl;
	}
}