#include "Aquecedor.hpp"

Aquecedor::Aquecedor() : Aquecedor::Aquecedor(20) {}
Aquecedor::Aquecedor(double valor){
    this->temperatura = valor;
}

void Aquecedor::aquecer(){
    this->temperatura += 5;
}
void Aquecedor::aquecer(double valor){
    this->temperatura += valor;
}

void Aquecedor::resfriar(){
    this->temperatura -= 5;
}
void Aquecedor::resfriar(double valor){
    this->temperatura -= valor;
}

double Aquecedor::getTemperatura(){
    return this->temperatura;
}
