#include "../../include/tela/TelaInicial.hpp"

TelaInicial::TelaInicial() : Tela() {
	this->titulo = "TELA INICIAL";
	this->opcoes.push_back(Opcao("L", "Realizar login como um bibliotecario"));
	this->opcoes.push_back(Opcao("C", "Cadastrar novo bibliotecario"));
}

string TelaInicial::getNomeTela() {
  	return "TelaLivros";
}
