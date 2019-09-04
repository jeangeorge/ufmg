#include "../../include/tela/TelaPrincipal.hpp"

TelaPrincipal::TelaPrincipal() : Tela() {
	this->titulo = "MENU PRINCIPAL";
	this->opcoes.push_back(Opcao("1", "Gerenciar Livros"));
	this->opcoes.push_back(Opcao("2", "Gerenciar Usuarios"));
	this->opcoes.push_back(Opcao("3", "Gerenciar Transacoes"));
}

string TelaPrincipal::getNomeTela() {
	return "TelaPrincipal";
}
