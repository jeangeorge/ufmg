#ifndef ARQUIVO_H
#define ARQUIVO_H

#include "AbrirArquivoException.hpp"
#include "../livro/Livro.hpp"
#include "../pessoa/Usuario.hpp"
#include "../pessoa/Bibliotecario.hpp"
#include "../transacao/Emprestimo.hpp"
#include "../transacao/Reserva.hpp"

#include <fstream>
#include <iterator>
#include <string>
#include <vector>

using std::ifstream;
using std::ios;
using std::ofstream;
using std::string;
using std::vector;

class Arquivo {
	public:
		Arquivo(string nome);
		~Arquivo();

		void atualizarDados(const vector<Bibliotecario>& vectorBibliotecarios);
		void atualizarDados(const vector<Usuario>& vectorUsuarios);
		void atualizarDados(const vector<Emprestimo>& vectorEmprestimos);
		void atualizarDados(const vector<Livro>& vectorLivros);
		void atualizarDados(const vector<Reserva>& vectorReservas);

		template<class T, class A> void obterDados(vector<T, A> &vectorParam) {
			string linha;
			arquivoLeitura.clear();
			arquivoLeitura.seekg(0, ios::beg);
			while (getline(arquivoLeitura, linha))
				alocarDadosLinha(linha, vectorParam);
		}

	private:
		string diretorio;
		ifstream arquivoLeitura;
		ofstream arquivoEscrita;

		void alocarDadosLinha(string linha, vector<Bibliotecario>& vectorBibliotecarios);
		void alocarDadosLinha(string linha, vector<Usuario>& vectorUsuarios);
		void alocarDadosLinha(string linha, vector<Emprestimo>& vectorEmprestimos);
		void alocarDadosLinha(string linha, vector<Livro>& vectorLivros);
		void alocarDadosLinha(string linha, vector<Reserva>& vectorReservas);

		void abrirModoLeitura();
		void abrirModoEscrita();
		void fecharModoLeitura();
		void fecharModoEscrita();
};

#endif
