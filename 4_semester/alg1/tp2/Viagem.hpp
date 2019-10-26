#ifndef VIAGEM_HPP
#define VIAGEM_HPP

#include "Ilha.hpp"

class Viagem
{
public:
  Viagem(int custo_total, int quantidade_ilhas, Ilha* ilhas);
  void viagemComRepeticao();
  void viagemSemRepeticao();
private:
  int custo_total, quantidade_ilhas;
  Ilha *ilhas;
  void merge(Ilha A[], int p, int q, int r);
  void mergeSort(Ilha A[], int p, int r);
  int max(int a, int b);
};

#endif