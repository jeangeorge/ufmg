#ifndef VIAGEM_HPP
#define VIAGEM_HPP

#include "Ilha.hpp"

class Viagem {
 public:
  Viagem(int custo_total, int quantidade_ilhas, Ilha *ilhas);
  ~Viagem();
  void viagemComRepeticao();
  void viagemSemRepeticao();

 private:
  int custo_total, quantidade_ilhas;
  Ilha *ilhas;
  void merge(Ilha ilhas[], int esquerda, int meio, int direita);
  void mergeSort(Ilha ilhas[], int esquerda, int direita);
  int max(int a, int b);
};

#endif