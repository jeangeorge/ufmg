#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Stats.hpp"

using namespace std;

int main(int argc, char** argv){
	// Meu objeto stats
	Stats* stats = new Stats;

	// Adiciono as acoes e mostro
	stats->adicionarAcoes();
	stats->mostrarAcoes();

	delete(stats);
	return 0;
}
