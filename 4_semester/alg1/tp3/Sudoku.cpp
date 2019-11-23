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

// Função que tenta resolver o Sudoku
bool Sudoku::resolver() {
  int linha, coluna;

  // Se não existe posição vazia no Sudoku, significa que todas as posições
  // foram preenchidas, portanto o Sudoku foi solucionado
  if (!existePosicaoVazia(linha, coluna)) {
    return true;
  }

  // Iteramos de 1 ao tamanho
  // Sudoku 9x9 possui dígitos entre 1-9
  // Sudoku 8x8 possui dígitos entre 1-8
  for (int digito = 1; digito <= tamanho; digito++) {
    // Avalia se não existem conflitos na possível atribuição
    if (!existeConflito(linha, coluna, digito)) {
      // Preenche aquela posição da tabela com o dígito em questão
      tabela[linha][coluna] = digito;

      // Tenta resolver o restante do Sudoku
      if (resolver()) {
        // Se conseguir resolver, retorna true
        return true;
      }

      // Caso não consiga resolver, redefine a posição.
      tabela[linha][coluna] = 0;
      // Voltará para o início do loop, testando para o valor dígito+1, e assim
      // sucessetivamente
    }
  }
  return false;  // this triggers backtracking
}

/* Função que verifica se existe posição não preenchida no Sudoku. Caso exista
 * posição vazia, retorna true e as variaveis 'linha' e 'coluna' conterão a
 * posição na tabela onde a célula vazia está. Caso não exista, retorna false
 */
bool Sudoku::existePosicaoVazia(int &linha, int &coluna) {
  for (linha = 0; linha < tamanho; linha++) {
    for (coluna = 0; coluna < tamanho; coluna++) {
      if (tabela[linha][coluna] == 0) {
        return true;
      }
    }
  }
  return false;
}

/* Dado uma linha fixada, verifica se o digito está presente naquela linha. */
bool Sudoku::existeConflitoLinha(int linha, int digito) {
  for (int coluna = 0; coluna < tamanho; coluna++) {
    if (tabela[linha][coluna] == digito) {
      return true;
    }
  }
  return false;
}

/* Dado uma linha coluna, verifica se o digito está presente naquela coluna. */
bool Sudoku::existeConflitoColuna(int coluna, int digito) {
  for (int linha = 0; linha < tamanho; linha++) {
    if (tabela[linha][coluna] == digito) {
      return true;
    }
  }
  return false;
}

/* Dado uma linha, uma coluna  e um dígito, avalia se é possível atribuir aquele
 * dígito a tabela[linha][coluna], levando em consideração o bloco */
bool Sudoku::existeConflitoBloco(int linha, int coluna, int num) {
  int inicio_bloco_linha = linha - linha % linhas;
  int inicio_bloco_coluna = coluna - coluna % colunas;
  for (int i = 0; i < linhas; i++) {
    for (int j = 0; j < colunas; j++) {
      if (tabela[i + inicio_bloco_linha][j + inicio_bloco_coluna] == num) {
        return true;
      }
    }
  }
  return false;
}

/* Verifica se será legal atribuir à posição [linha,coluna] o dígito em
 * questão. A atribuição será válida se, e somente se, não exister um outro
 * dígito igual na mesma linha, mesma coluna e mesmo bloco. Se por algum motivo
 * a posição [linha][coluna] da matriz já estiver preenchida também
 * consideraremos como um conflito.
 */
bool Sudoku::existeConflito(int linha, int coluna, int digito) {
  if (existeConflitoLinha(linha, digito)) {
    return true;
  }
  if (existeConflitoColuna(coluna, digito)) {
    return true;
  }
  if (existeConflitoBloco(linha, coluna, digito)) {
    return true;
  }
  if (tabela[linha][coluna] != 0) {
    return true;
  }
  return false;
}

// Função que percorre a matriz/Sudoku e a mostra
void Sudoku::mostrar() {
  for (int i = 0; i < tamanho; i++) {
    for (int j = 0; j < tamanho; j++) {
      cout << tabela[i][j] << " ";
    }
    cout << endl;
  }
}