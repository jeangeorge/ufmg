#ifndef EMPRESTIMO_H
#define EMPRESTIMO_H

#include <iostream>
#include <sstream>
#include <string>

using std::cout;
using std::endl;
using std::string;
using std::stringstream;

class Emprestimo {
	public:
		Emprestimo(int idEmprestimo, int idLivro, int idUsuario, int diaRealizacao,
			int mesRealizacao, int anoRealizacao, int valorMulta);
		~Emprestimo();

		string toString();
		string toStringToSave();

		void criarDataDevolucao();

		int getIdEmprestimo();
		void setIdEmprestimo(int idEmprestimo);

		int getIdLivro();
		void setIdLivro(int idLivro);

		int getIdUsuario();
		void setIdUsuario(int idUsuario);

		int getValorMulta();
		void setValorMulta(int valorMulta);

		int getDiaDevolucao();
		int getMesDevolucao();
		int getAnoDevolucao();
		void setDiaRealizacao(int);
		void setMesRealizacao(int);
		void setAnoRealizacao(int);
		void setDiaDevolucao(int);
		void setMesDevolucao(int);
		void setAnoDevolucao(int);

	private:
		int idEmprestimo, idLivro, idUsuario, valorMulta, diaRealizacao,
			diaDevolucao, mesRealizacao, mesDevolucao, anoRealizacao, anoDevolucao;
};

#endif
