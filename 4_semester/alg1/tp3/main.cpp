#include <fstream>
#include <iostream>

#include "Sudoku.hpp"

using namespace std;

int main(int argc, char **argv) {
  ifstream arquivo(argv[1]);

  // Se arquivo não foi aberto, já encerra o programa
  if (!arquivo.is_open()) {
    return 0;
  }

  // Cria um objeto sudoku, passando o arquivo
  Sudoku *sudoku = new Sudoku(&arquivo);

  // Fecha o arquivo, se não fechar encerra o programa
  arquivo.close();
  if (arquivo.is_open()) {
    return 0;
  }

  // Tenta resolver o sudoku
  if (sudoku->SolveSudoku()) {
    cout << "solucao" << endl;
  } else {
    cout << "sem solucao" << endl;
  }
  sudoku->mostrar();
  // delete solucao;
  delete sudoku;

  return 0;
}