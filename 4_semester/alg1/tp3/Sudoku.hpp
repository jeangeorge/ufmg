#ifndef SUDOKU_HPP
#define SUDOKU_HPP

#include <fstream>

class Sudoku {
 public:
  Sudoku(std::ifstream *arquivo);
  ~Sudoku();
  int **getSolucao();
  void imprimirMatriz(int **matriz, int m, int n);
  void mostrar();

  bool SolveSudoku();
  bool FindUnassignedLocation(int &row, int &col);
  bool UsedInRow(int row, int num);
  bool UsedInCol(int col, int num);
  bool UsedInBox(int boxStartRow, int boxStartCol, int num);
  bool isSafe(int row, int col, int num);

 private:
  int tamanho, linhas, colunas;
  int **tabela;
  int **solucao;
};

#endif