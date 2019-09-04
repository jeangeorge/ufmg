#include "Poupanca.hpp"

Poupanca::Poupanca() : Poupanca::Poupanca(0) {}
Poupanca::Poupanca(double valor){
    this->saldoPoupanca = valor;
}

double Poupanca::taxaDeJurosAnual = 0.05;

void Poupanca::calcularJurosMensal(){
    this->saldoPoupanca += this->saldoPoupanca * (this->taxaDeJurosAnual)/12;
}

void Poupanca::depositarValor(double valor){
    this->saldoPoupanca += valor;
}

void Poupanca::sacarValor(double valor){
    this->saldoPoupanca -= valor;
}

void Poupanca::setTaxaDeJurosAnual(double novaTaxa){
    Poupanca::taxaDeJurosAnual = novaTaxa;
}

double Poupanca::getSaldoPoupanca(){
    return(this->saldoPoupanca);
}
