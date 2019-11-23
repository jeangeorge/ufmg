#include <fstream>
#include <iostream>

#include "Sudoku.hpp"

using namespace std;

int main(int argc, char **argv) {
  // Abre o arquivo de acordo com o nome recebido no argumento
  ifstream arquivo(argv[1]);

  // Se arquivo não foi aberto, já encerra o programa
  if (!arquivo.is_open()) {
    return 0;
  }

  // Cria um objeto sudoku, passando o arquivo como parâmetro
  Sudoku *sudoku = new Sudoku(&arquivo);

  // Fecha o arquivo, se não fechar encerra o programa
  arquivo.close();
  if (arquivo.is_open()) {
    return 0;
  }

  // Tenta resolver o sudoku
  if (sudoku->resolver()) {
    cout << "solucao" << endl;
  } else {
    cout << "sem solucao" << endl;
  }

  // Mostra a solução encontrada.
  // Caso não encontre solução mostra até onde o algoritmo resolveu.
  sudoku->mostrar();

  // Destrói o objeto Sudoku
  delete sudoku;

  return 0;
}