#ifndef STATS_H
#define STATS_H

#include <iostream>
#include <map>
#include <vector>

using namespace std;

// Defino a estrutura stats
struct Stats{

	// As acoes são uma dupla -> (nome) e (vector dos valores de acao)
	map<string,vector<float>> acoes;

	void adicionarAcoes();
	void mostrarAcoes();
};

#endif
