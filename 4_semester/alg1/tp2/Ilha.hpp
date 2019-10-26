
#ifndef ILHA_HPP
#define ILHA_HPP

// Uma ilha é composta de um custo e uma pontuacao
class Ilha {
 public:
  Ilha(int custo, int pontuacao);
  Ilha();
  ~Ilha();
  int getCusto();
  int getPontuacao();
  double getCustoBeneficio();

 private:
  int custo, pontuacao;
};

#endif
