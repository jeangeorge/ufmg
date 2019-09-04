#include "MiniSisu.hpp"
#include <sstream>
#include <iomanip>
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;

MiniSisu::MiniSisu() {
	// Inicializa as listas de cursos e candidatos
	cursos = new Lista<Curso>();
	candidatos = new Lista<Candidato>();

	int numCursos, numCandidatos;

	// Le a quantidade de cursos e alunos
	cin >> numCursos >> numCandidatos;

	preencherCursos(numCursos);
	preencherCandidatos(numCandidatos);

	candidatos->ordenar();
	alocarCandidatos();
	//mostrarResultado();
}

MiniSisu::~MiniSisu() {
	delete cursos;
	delete candidatos;
}

void MiniSisu::preencherCursos(int numCursos) {
	// Le os dados dos cursos
	for (int i=0; i<numCursos; i++) {
		string nomeCurso;
		int numVagas;

		cin.ignore();
		getline(cin, nomeCurso, '\n');

		cin >> numVagas;

		Curso curso(i,nomeCurso,numVagas);
		cursos->inserir(curso);
	}
}

void MiniSisu::preencherCandidatos(int numCandidatos) {
	// Le os dados dos alunos
	for (int i=0; i<numCandidatos; i++) {
		string nomeAluno;
		double nota;
		int opcao1, opcao2;

		cin.ignore();
		getline(std::cin, nomeAluno, '\n');

		cin >> nota;
		cin >> opcao1 >> opcao2;

		Candidato candidato(i,nomeAluno,nota,opcao1,opcao2);
		candidatos->inserir(candidato);
	}
}

void MiniSisu::alocarCandidatos() {
	// Chama a função para ordenar os candidatos por ordem decrescente de nota e de escolhas de curso
	No<Curso>* noCurso = new No<Curso>();
	for (noCurso = cursos->primeiro; noCurso != nullptr; noCurso = noCurso->proximo) {
		No<Candidato>* noCandidato = new No<Candidato>();
		for (noCandidato = candidatos->primeiro; noCandidato != nullptr; noCandidato = noCandidato->proximo) {
			// Caso tenha vagas disponiveis para o curso
			if (noCurso->dado.vagasDisponiveis > 0) {
				// E o candidato escolheu este curso como primeira opcao
				if ((noCurso->dado.id == noCandidato->dado.opcao1 || noCurso->dado.id == noCandidato->dado.opcao2) && noCandidato->dado.aprovado == false) {
					// Aprovado na primeira opcao
					noCandidato->dado.aprovado = true;
					noCurso->dado.aprovados.inserir(noCandidato->dado);
					noCurso->dado.vagasDisponiveis--;
				}
			}
			// Caso nao tenha  vagas disponiveis
			else {
				// E o candidato tenha escolhido este curso
				if (noCurso->dado.id == noCandidato->dado.opcao1 || noCurso->dado.id == noCandidato->dado.opcao2) {
					// Entra para a lista de espera
					noCurso->dado.listaEspera.inserir(noCandidato->dado);
				}
			}
		}
		// Ordena os aprovados e a lista de espera, não estejam vazias.
		if(noCurso->dado.aprovados.primeiro)
			noCurso->dado.aprovados.ordenar();
		if(noCurso->dado.listaEspera.primeiro)
			noCurso->dado.listaEspera.ordenar();
	}
}

void MiniSisu::mostrarResultado() {
	// Inicia no primeiro no da lista de cursos
	No<Curso> *noCurso = cursos->primeiro;
	while (noCurso) {
		No<Candidato> *noCandidato = noCurso->dado.aprovados.primeiro;
		cout << noCurso->dado.nome << " ";
		std::cout << std::fixed;
		std::cout << std::setprecision(2);
		if (noCandidato) {
			if (noCurso->dado.vagasDisponiveis == 0) {
				cout << noCurso->dado.aprovados.ultimo->dado.nota << endl;
			} else {
				cout << 0.00 << endl;
			}
		} else {
			cout << 0.00 << endl;
		}
		cout << "Classificados" << endl;
		while(noCandidato) {
			cout << noCandidato->dado.nome << " ";
			std::cout << std::fixed;
			std::cout << std::setprecision(2);
			cout << noCandidato->dado.nota << endl;
			noCandidato = noCandidato->proximo;
		}
		cout << "Lista de espera" << endl;
		noCandidato = noCurso->dado.listaEspera.primeiro;
		while(noCandidato) {
			cout << noCandidato->dado.nome << " ";
			std::cout << std::fixed;
			std::cout << std::setprecision(2);
			cout << noCandidato->dado.nota << endl;
			noCandidato = noCandidato->proximo;
		}
		cout << endl;
		noCurso = noCurso->proximo;
	}
}
