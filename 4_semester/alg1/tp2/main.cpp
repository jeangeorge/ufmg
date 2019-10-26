#include <fstream>
#include <iostream>

#include "Ilha.hpp"
#include "Viagem.hpp"

#include <chrono>
#include <iomanip>
using namespace std::chrono;

using namespace std;

int main(int argc, char **argv) {
  ifstream arquivo(argv[1]);

  // Se arquivo não foi aberto, já encerra o programa
  if (!arquivo.is_open()) {
    return 0;
  }
  // custo_total em reais e quantidade de ilhas visitadas
  int custo_total, quantidade_ilhas;

  arquivo >> custo_total >> quantidade_ilhas;  // Lê o custo e a quantidade
  Ilha *ilhas = new Ilha[quantidade_ilhas];    // Cria um array de ilhas de
                                               // tamanho "quantidade_ilhas"

  // Preenche o array de ilhas
  for (int i = 0; i < quantidade_ilhas; i++) {
    int custo_diario, pontuacao;
    arquivo >> custo_diario >> pontuacao;
    ilhas[i] = Ilha(custo_diario, pontuacao);
  }

  // Fecha o arquivo, se não fechar encerra o programa
  arquivo.close();
  if (arquivo.is_open()) {
    return 0;
  }

  // Cria uma viagem
  Viagem *viagem = new Viagem(custo_total, quantidade_ilhas, ilhas);

  // Calcula as duas soluções

  double guloso[11], dinamico[11];
  for (int i = 0; i < 11; i++) {
    auto start = high_resolution_clock::now();

    viagem->viagemComRepeticao();

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    guloso[i] = duration.count();
  }

  for (int i = 0; i < 11; i++) {
    auto start = high_resolution_clock::now();

    viagem->viagemSemRepeticao();

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    dinamico[i] = duration.count();
  }

  cout << "TEMPOS GULOSO:" << endl;
  for (int i = 1; i < 11; i++) {
    cout << std::setprecision(2) << std::fixed << guloso[i] << " ";
  }
  cout << endl;
  cout << "TEMPOS dinamico:" << endl;
  for (int i = 1; i < 11; i++) {
    cout << std::setprecision(2) << dinamico[i] << " ";
  }
  cout << endl;

  delete[] ilhas;
  delete viagem;

  return 0;
}