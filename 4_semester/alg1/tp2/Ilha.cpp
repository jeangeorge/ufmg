#include "Ilha.hpp"

Ilha::Ilha(int ilha, int pontuacao) : custo(ilha), pontuacao(pontuacao) {}

Ilha::Ilha() {}

Ilha::~Ilha() {}

double Ilha::getCustoBeneficio() { return this->custo * 1.0 / this->pontuacao; }

int Ilha::getCusto() { return this->custo; }

int Ilha::getPontuacao() { return this->pontuacao; }