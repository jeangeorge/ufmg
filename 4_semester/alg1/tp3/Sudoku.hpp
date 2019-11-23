#ifndef SUDOKU_HPP
#define SUDOKU_HPP

#include <fstream>

class Sudoku {
 public:
  Sudoku(std::ifstream *arquivo);
  ~Sudoku();
  void mostrar();
  bool resolver();

 private:
  int tamanho, linhas, colunas;
  int **tabela;
  bool existePosicaoVazia(int &linha, int &coluna);
  bool existeConflitoLinha(int linha, int digito);
  bool existeConflitoColuna(int coluna, int digito);
  bool existeConflitoBloco(int linha, int coluna, int digito);
  bool existeConflito(int linha, int coluna, int digito);
};

#endif