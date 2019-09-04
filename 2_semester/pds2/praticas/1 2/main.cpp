#include <iostream>
#include <string>
#include <vector>

#include "Circunferencia.hpp"

using namespace std;

int main(int argc, char** argv){
	vector<Circunferencia> circunferencias; // Um vector para armazenar as circunferencias
	vector<Circunferencia>::const_iterator iterator1; // Meu iterator para o vector
	vector<Circunferencia>::const_iterator iterator2; // Meu iterator para o vector

	string str,linha;

	int id, x, y, raio;

	// Leio id por id
	while(cin >> id){
		// Crio uma circunferencia auxiliar
		Circunferencia circ;

		// Leio as coordenadas e o raio, respectivamente
		cin >> x;
		cin >> y;
		cin >> raio;

		// Atribuo os valores no circulo
		circ.id = id;
		circ.centro.x = x;
		circ.centro.y = y;
		circ.raio = raio;

		// Agora que montei a circunferencia basta coloca-la no vector
		circunferencias.push_back(circ);

	}

	// Nesse ponto já tenho tudo dentro do vector
	// Vou percorrer o vector
	for(unsigned i=0; i<circunferencias.size(); ++i){
		cout << circunferencias[i].id;
    	// Vou percorrer o vector novamente para comparar as circunferencias duas a duas
		for(unsigned int j=0; j<circunferencias.size(); ++j){
        	// So vou comparar os diferentes obviamente
			if(circunferencias[i].id != circunferencias[j].id){
				// Caso haja interesecao vou colocar no output
				if(circunferencias[i].verificaIntersecao(circunferencias[j])){
					cout << " " << circunferencias[j].id;
				}
			}
		}
		cout << endl;
	}

	return 0;
}
