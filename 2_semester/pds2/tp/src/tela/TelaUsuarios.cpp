#include "../../include/tela/TelaUsuarios.hpp"

TelaUsuarios::TelaUsuarios() : Tela() {
	this->titulo = "GERENCIAMENTO DE USUARIOS";
	this->opcoes.push_back(Opcao("V", "Voltar para o Menu Principal"));
	this->opcoes.push_back(Opcao("1", "Visualizar todos os Usuarios"));
	this->opcoes.push_back(Opcao("2", "Visualizar um Usuario especifico"));
	this->opcoes.push_back(Opcao("3", "Atualizar dados de um Usuario"));
	this->opcoes.push_back(Opcao("4", "Adicionar um novo Usuario na base de dados"));
	this->opcoes.push_back(Opcao("5", "Remover um Usuario da base de dados"));
}

string TelaUsuarios::getNomeTela() {
	return "TelaUsuarios";
}
