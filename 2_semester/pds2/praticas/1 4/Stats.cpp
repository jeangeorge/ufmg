#include "Stats.hpp"

#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;

// Le as acoes do teclado e vai colocando no map
void Stats::adicionarAcoes(){
	string nome;
	float valor;

	// Para cada nome
	while(cin >> nome){
		// Leio um valor
		cin >> valor;

		// E adiciono no vector daquele indice (nome)
		acoes[nome].push_back(valor);
	}
}

// Simplesmente printa na tela conforme o enunciado requer
void Stats::mostrarAcoes(){
	map<string, vector<float>>::const_iterator itr;  // Iterador só pra ir percorrendo
	float minimo, maximo, media;
	unsigned int i;

	cout << fixed << showpoint << setprecision(2); // Fixando duas casas decimais

	// Vou do inicio até o fim do map
	for (itr = acoes.begin(); itr != acoes.end(); ++itr){
		minimo = -1; maximo = -1; media = 0;
		cout << itr->first;
		for(i=0; i<itr->second.size();++i){
			cout << " " << itr->second[i];

			if(minimo == -1 || itr->second[i] < minimo)
				minimo = itr->second[i];

			if(maximo == -1 || itr->second[i] > maximo)
				maximo = itr->second[i];

			media += itr->second[i];
		}

		media = media/i;

		cout << " | " << minimo << " " << maximo << " " << media << endl;
	}
}
