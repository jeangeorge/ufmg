#include <iostream>

#include "Viagem.hpp"

using namespace std;

// Construtor recebe o custo total máximo da viagem, a quantidade de ilhas a serem visitadas e um array de ilhas (contendo o custo diário e a pontuação da ilha)
Viagem::Viagem(int custo_total, int quantidade_ilhas, Ilha *ilhas) : custo_total(custo_total), quantidade_ilhas(quantidade_ilhas), ilhas(ilhas) {}

// Viagem com repetição: algoritmo guloso, complexidade n log m
void Viagem::viagemComRepeticao()
{
  // Primeiro ordena as ilhas por custo-beneficio (crescente) -> complexidade n log n
  mergeSort(ilhas, 0, quantidade_ilhas - 1);

  int i = 0; // índice para acessar as ilhas
  int pontuacao = 0, dias = 0; // variáveis somadoras, serão o resultado final
  int dinheiro_disponivel = this->custo_total; // quantidade de dinheiro atualmente disponível, decresce conforme executamos

  // Inicia a iteração sobre as ilhas
  while (i < this->quantidade_ilhas)
  {
    // dinheiro_disponivel = 0 ou dinheiro_disponivel negativo quer dizer que não é possível mais fazer visitas porque o dinheiro acabou
    if (dinheiro_disponivel <= 0)
    {
      break;
    }
    // Calcula quantas vezes é possível visitar a ilha atual
    int num_visitas = dinheiro_disponivel / ilhas[i].getCusto();
    // Atualiza a pontuação e os dias
    dias += num_visitas;
    pontuacao += (num_visitas * ilhas[i].getPontuacao());
    // Por fim deve atualizar o dinheiro disponível
    dinheiro_disponivel -= (num_visitas * ilhas[i].getCusto());
    i++;
  }
  // Mostra o resultado encontrado
  cout << pontuacao << " " << dias << endl;
}

void Viagem::viagemSemRepeticao()
{
  int i, j; // i,j são índices para percorrer a matriz 'mochila'
  int custo_limite = custo_total;
  int pontuacao, dias = 0; // Variáveis para armazenar o resultado final

  // Cria nossa mochila de tamanho 0..quantidade_ilhas+1 x 0..custo_total+1
  int** mochila = new int*[quantidade_ilhas+1];
  for (i = 0; i<=quantidade_ilhas; i++) {
    mochila[i] = new int[custo_total+1];
  }

  // Percorre a matriz mochila e a preenche
  for (i = 0; i <= quantidade_ilhas; i++)
  {
    for (j = 0; j <= custo_total; j++)
      if (i == 0 || j == 0)
      {
        // primeira linha e primeira linha da matriz são sempre 0
        mochila[i][j] = 0;
      }
      else if (ilhas[i-1].getCusto() <= j)
      {
        // Se o custo da linha acima é menor que o custo que estamos avaliando (j)
        // é preciso ver se é mais conveniente colocar a pontuação do índice atual ou não colocar a pontuação
        mochila[i][j] = max(ilhas[i - 1].getPontuacao() + mochila[i - 1][j - ilhas[i - 1].getCusto()], mochila[i - 1][j]);
      }
      else
      {
        // apenas repete o valor da linha linha acima & mesma coluna
        mochila[i][j] = mochila[i-1][j];
      }
  }

  // No fim das contas a pontuação máxima possível vai ser a que se encontra na última linha e última coluna da matriz
  pontuacao = mochila[quantidade_ilhas][custo_total];

  // Agora é preciso fazer o cálculo dos dias
  // Percorremos a partir do final da mochila
  for (i = quantidade_ilhas; i > 0; i --) {
    if (pontuacao <= 0 || pontuacao == mochila[i-1][custo_limite]) {
      continue;
    } else {
      dias++;
      pontuacao -= ilhas[i-1].getPontuacao();
      custo_limite -= ilhas[i-1].getCusto();
    }
  }

  // Recalculamos a pontuação final
  pontuacao = mochila[quantidade_ilhas][custo_total];

  cout << pontuacao << " " << dias << endl;
}

// Merge -> juntar os dois vetores
void Viagem::merge(Ilha ilhas[], int esquerda, int direita, int r)
{
  // Calcula o tamanho do array da esquerda e do array da direita
  int tamanho_esquerda = direita - esquerda + 1, tamanho_direita = r - direita, i, j, k;

  // Inicializa os dois vetores esquerda e direita
  Ilha vetor_esquerda[tamanho_esquerda], vetor_direita[tamanho_direita];
  for (i = 0; i < tamanho_esquerda; i++)
  {
    vetor_esquerda[i] = ilhas[esquerda + i];
  }
  for (j = 0; j < tamanho_direita; j++)
  {
    vetor_direita[j] = ilhas[direita + j + 1];
  }

  i = 0, j = 0;

  // Compara e faz o merge num novo array na ordem correta
  for (k = esquerda; i < tamanho_esquerda && j < tamanho_direita; k++)
  {
    if (vetor_esquerda[i].getCustoBeneficio() < vetor_direita[j].getCustoBeneficio())
    {
      ilhas[k] = vetor_esquerda[i++];
    }
    else
    {
      ilhas[k] = vetor_direita[j++];
    }
  }

  // Caso o vetor da esquerda tenha mais elementos que o vetor da direita deve colocar todos os elementos restantes do vetor da esquerda no vetor resultante
  while (i < tamanho_esquerda)
  {
    ilhas[k++] = vetor_esquerda[i++];
  }

  // Caso o vetor da esquerda tenha mais elementos que o vetor da direita deve colocar todos os elementos restantes do vetor da esquerda no vetor resultante
  while (j < tamanho_direita)
  {
    ilhas[k++] = vetor_direita[j++];
  }
}

// Função mergesort, ordena o array em complexidade n log n
void Viagem::mergeSort(Ilha ilhas[], int esquerda, int direita)
{
  int meio;
  if (esquerda < direita)
  {
    meio = (esquerda + direita) / 2;
    mergeSort(ilhas, esquerda, meio);
    mergeSort(ilhas, meio + 1, direita);
    merge(ilhas, esquerda, meio, direita);
  }
}

// Função para retornar o máximo entre dois inteiros
int Viagem::max(int a, int b)
{
  if (a > b)
    return a;
  else
    return b;
}