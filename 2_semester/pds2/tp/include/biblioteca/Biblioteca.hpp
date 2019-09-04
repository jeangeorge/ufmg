#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include "../arquivos/Arquivo.hpp"
#include "../data/Data.hpp"
#include "../livro/Livro.hpp"
#include "../pessoa/Bibliotecario.hpp"
#include "../pessoa/Usuario.hpp"
#include "../tela/TelaPrincipal.hpp"
#include "../tela/TelaLivros.hpp"
#include "../tela/TelaUsuarios.hpp"
#include "../tela/TelaTransacoes.hpp"
#include "../transacao/Emprestimo.hpp"
#include "../transacao/Reserva.hpp"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::vector;
using std::string;

class Biblioteca {
	public:
		Biblioteca(string nome, string endereco, string telefone);
		~Biblioteca();

		string getNome();
		void setNome(string);

		string getEndereco();
		void setEndereco(string);

		string getTelefone();
		void setTelefone(string);

	private:
		Bibliotecario *bibliotecarioAtual;

		Arquivo *arquivoBibliotecarios, *arquivoUsuarios,
				*arquivoLivros, *arquivoEmprestimos, *arquivoReservas;

		Tela* telaAtual;

		vector<Bibliotecario> vectorBibliotecarios;
		vector<Usuario> vectorUsuarios;
		vector<Livro> vectorLivros;
		vector<Emprestimo> vectorEmprestimos;
		vector<Reserva> vectorReservas;

		Data data;
		string nome, endereco, telefone;

		void iniciarSistema();
		bool carregarArquivos();
		void exibirConfirmacaoLogin();
		void exibirMenu();
		void mostrarData();
		void atualizarStatus();
		bool getEntradaValida(string& entrada, bool bloquearEntradaVazia);
		bool getEntradaInt(int& entrada);
		bool confirmarAcao(string);
		void removerEspacos(string& linha);

		void verificarOpcaoPorTela(string opcao);
		void verificarOpcaoTelaPrincipal(string opcao);
		void verificarOpcaoTelaLivros(string opcao);
		void verificarOpcaoTelaUsuarios(string opcao);
		void verificarOpcaoTelaTransacoes(string opcao);

		void listarLivros();
		void pesquisarLivro();
		void atualizarLivro();
		bool obterDadosAtualizarLivro(Livro& l);
		void adicionarLivro();
		bool existeLivro(string nome, string autor);
		Livro* existeLivro(int id);
		bool construirNovoLivro(Livro*& l);
		void removerLivro();

		void listarUsuarios();
		void pesquisarUsuario();
		void atualizarUsuario();
		bool obterDadosAtualizarUsuario(Usuario& u);
		void verificarDefinirDadosUsuario(Usuario& u, string dados[8]);
		void adicionarUsuario();
		bool existeUsuario(string cpf);
		Usuario* existeUsuario(int idUsuario);
		bool construirNovoUsuario(Usuario*& u);
		void removerUsuario();

		int getIdNovoLivro();
		int getIdNovoUsuario();
		int getIdNovoEmprestimo();
		int getIdNovaReserva();

		void listarEmprestimos();
		void pesquisarEmprestimo();
		void realizarEmprestimo();
		bool verificarCondicoesEmprestimo(int idLivro, int idUsuario);
		void renovarEmprestimo();
		void realizarDevolucao();

		void listarReservas();
		void pesquisarReserva();
		void realizarReserva();
		bool verificarCondicoesReserva(int idLivro, int idUsuario);
		void cancelarReserva();
		void cancelarReserva(vector<Reserva>& vectorReservas, int posicaoReserva);
};

#endif
