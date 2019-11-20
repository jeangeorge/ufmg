#include <iostream>

#include "Sudoku.hpp"

using namespace std;

// Construtor recebe somente o arquivo e partir dele preenche os dados do sudoku
Sudoku::Sudoku(std::ifstream *arquivo) {
  // Salva o tamanho, colunaunas por quadrante e linhas por quadrante
  *arquivo >> tamanho >> colunas >> linhas;

  // Instancia a matriz alocada dinamicamente
  tabela = new int *[tamanho];
  for (int i = 0; i < tamanho; i++) {
    tabela[i] = new int[tamanho];
  }

  // Preenche os dados da tabela
  for (int i = 0; i < tamanho; i++) {
    for (int j = 0; j < tamanho; j++) {
      *arquivo >> tabela[i][j];
    }
  }
}

// Destrutor desaloca a memoria para a tabela do sudoku
Sudoku::~Sudoku() {
  for (int i = 0; i < tamanho; i++) {
    delete[] tabela[i];
  }
  delete[] tabela;
}

// Retorna a solução armazenada para o sudoku
int **Sudoku::getSolucao() { return solucao; }

// Método para printar uma matriz
void Sudoku::imprimirMatriz(int *matriz[], int m, int n) {
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      cout << matriz[i][j] << " ";
    }
    cout << endl;
  }
}

bool Sudoku::SolveSudoku() {
  int linha, coluna;

  // If there is no unassigned location,
  // we are done
  if (!FindUnassignedLocation(linha, coluna)) return true;  // success!

  // consider digits 1 to 9
  for (int num = 1; num <= tamanho; num++) {
    // if looks promising
    if (isSafe(linha, coluna, num)) {
      // make tentative assignment
      tabela[linha][coluna] = num;

      // return, if success, yay!
      if (SolveSudoku()) return true;

      // failure, unmake & try again
      tabela[linha][coluna] = 0;
    }
  }
  return false;  // this triggers backtracking
}

/* Searches the grid to find an entry that is
still unassigned. If found, the reference
parameters row, col will be set the location
that is unassigned, and true is returned.
If no unassigned entries remain, false is returned. */
bool Sudoku::FindUnassignedLocation(int &row, int &col) {
  for (row = 0; row < tamanho; row++)
    for (col = 0; col < tamanho; col++)
      if (tabela[row][col] == 0) return true;
  return false;
}

/* Returns a boolean which indicates whether
an assigned entry in the specified row matches
the given number. */
bool Sudoku::UsedInRow(int row, int num) {
  for (int col = 0; col < tamanho; col++)
    if (tabela[row][col] == num) return true;
  return false;
}

/* Returns a boolean which indicates whether
an assigned entry in the specified column
matches the given number. */
bool Sudoku::UsedInCol(int col, int num) {
  for (int row = 0; row < tamanho; row++)
    if (tabela[row][col] == num) return true;
  return false;
}

/* Returns a boolean which indicates whether
an assigned entry within the specified linhasxcolunas box
matches the given number. */
bool Sudoku::UsedInBox(int boxStartRow, int boxStartCol, int num) {
  for (int row = 0; row < linhas; row++)
    for (int col = 0; col < colunas; col++)
      if (tabela[row + boxStartRow][col + boxStartCol] == num) return true;
  return false;
}

/* Returns a boolean which indicates whether
it will be legal to assign num to the given
row, col location. */
bool Sudoku::isSafe(int row, int col, int num) {
  /* Check if 'num' is not already placed in
  current row, current column and current  box */
  return !UsedInRow(row, num) && !UsedInCol(col, num) &&
         !UsedInBox(row - row % linhas, col - col % colunas, num) &&
         tabela[row][col] == 0;
}

void Sudoku::mostrar() {
  for (int i = 0; i < tamanho; i++) {
    for (int j = 0; j < tamanho; j++) {
      cout << tabela[i][j] << " ";
    }
    cout << endl;
  }
}