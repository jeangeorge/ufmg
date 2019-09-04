#include "Empregado.hpp"

using std::cout;

Empregado::Empregado(const string& primeiro, const string& ultimo,
                     const string& cpf_param, int mes, int dia, int ano)
    : primeiroNome(primeiro),
      ultimoNome(ultimo),
      cpf(cpf_param),
      dataNascimento(mes, dia, ano) {}

Empregado::~Empregado(){

}

Data Empregado::getDataNascimento() const { return dataNascimento; }

void Empregado::setDataNascimento(int mes, int dia, int ano) {
  dataNascimento.setData(mes, dia, ano);
}

string Empregado::getPrimeiroNome() const { return primeiroNome; }

void Empregado::setPrimeiroNome(const string& primeiro) {
  primeiroNome = primeiro; }

string Empregado::getUltimoNome() const { return ultimoNome; }

void Empregado::setUltimoNome(const string& ultimo) { ultimoNome = ultimo; }

string Empregado::getCPF() const { return cpf; }

void Empregado::setCPF(const string& cpf_param) { cpf = cpf_param; }

void Empregado::imprime() const {
  cout << getPrimeiroNome() << ' ' << getUltimoNome()
       << "\nnascimento: " << getDataNascimento() << "\ncpf: " << getCPF();
}
