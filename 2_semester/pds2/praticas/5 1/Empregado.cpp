#include "Empregado.hpp"

Empregado::Empregado(const string& primeiro, const string& ultimo, const string& cpf_param, 
  int mes, int dia, int ano) : primeiroNome(primeiro), ultimoNome(ultimo), 
  cpf(cpf_param), dataNascimento(mes, dia, ano) {}

void Empregado::setPrimeiroNome(const string& primeiro)
{
  primeiroNome = primeiro;
}

string Empregado::getPrimeiroNome() const
{
  return primeiroNome;
}

void Empregado::setUltimoNome(const string& ultimo)
{
  ultimoNome = ultimo;
}

string Empregado::getUltimoNome() const
{
  return ultimoNome;
}

void Empregado::setCPF(const string& cpf_param)
{
  cpf = cpf_param;
}

string Empregado::getCPF() const
{
  return cpf;
}

void Empregado::setDataNascimento(int mes, int dia, int ano)
{
  dataNascimento.setData(mes, dia, ano);
}

Data Empregado::getDataNascimento() const
{
  return dataNascimento;
}

void Empregado::imprime() const
{
  cout << getPrimeiroNome() << ' ' << getUltimoNome() 
    << "\nnascimento: " << getDataNascimento()
    << "\ncpf: " << getCPF();
}
