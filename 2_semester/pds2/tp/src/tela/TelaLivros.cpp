#include "../../include/tela/TelaLivros.hpp"

TelaLivros::TelaLivros() : Tela() {
	this->titulo = "GERENCIAMENTO DE LIVROS";
	this->opcoes.push_back(Opcao("V", "Voltar para o Menu Principal"));
	this->opcoes.push_back(Opcao("1", "Visualizar todos os livros"));
	this->opcoes.push_back(Opcao("2", "Visualizar um livro especifico"));
	this->opcoes.push_back(Opcao("3", "Atualizar dados de um livro"));
	this->opcoes.push_back(Opcao("4", "Adicionar um novo livro na base de dados"));
	this->opcoes.push_back(Opcao("5", "Remover um livro da base de dados"));
}

string TelaLivros::getNomeTela() {
	return "TelaLivros";
}
