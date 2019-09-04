#include "../../include/tela/TelaTransacoes.hpp"

TelaTransacoes::TelaTransacoes() : Tela() {
	this->titulo = "GERENCIAMENTO DE TRANSACOES";
	this->opcoes.push_back(Opcao("V", "Voltar para o Menu Principal"));
	this->opcoes.push_back(Opcao("1", "Visualizar todos os Emprestimos"));
	this->opcoes.push_back(Opcao("2", "Visualizar um Emprestimo especifico"));
	this->opcoes.push_back(Opcao("3", "Visualizar todas as Reservas"));
	this->opcoes.push_back(Opcao("4", "Visualizar uma Reserva especifica"));
	this->opcoes.push_back(Opcao("5", "Realizar um Emprestimo"));
	this->opcoes.push_back(Opcao("6", "Realizar uma Devolucao"));
	this->opcoes.push_back(Opcao("7", "Realizar uma Reserva"));
	this->opcoes.push_back(Opcao("8", "Cancelar uma Reserva"));
	this->opcoes.push_back(Opcao("9", "Renovar um Emprestimo"));
}

string TelaTransacoes::getNomeTela() {
	return "TelaTransacoes";
}
