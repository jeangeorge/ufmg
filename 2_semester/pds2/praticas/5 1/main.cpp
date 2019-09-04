#include <iostream>
using std::cout;
using std::endl;
using std::fixed;
#include <iomanip>
using std::setprecision;
#include <vector>
using std::vector;
#include <typeinfo>
#include <ctime>
using std::time_t;
using std::time;
using std::localtime;
using std::strftime;
#include <cstdlib>
using std::atoi;

#include "Empregado.hpp"
#include "EmpregadoSalariado.hpp"
#include "EmpregadoPorHora.hpp"
#include "EmpregadoComissionado.hpp"
#include "EmpregadoComissionadoBase.hpp"
#include "Data.hpp"

// retorna o mes corrente
int determinaMes()
{
  time_t tempoAtual;
  char stringMes[3];
  time(&tempoAtual);
  strftime(stringMes, 3, "%m", localtime(&tempoAtual));
  return atoi(stringMes);
}

int main()
{
  cout << fixed << setprecision(2);
  vector<Empregado*> empregados(4);
  empregados[0] = new EmpregadoSalariado("Joao", "Mario", "111-111-111.11", 6, 15, 1994, 800);
  empregados[1] = new EmpregadoPorHora("Karen", "Ferreira", "222-222-222.22", 12, 29, 1999, 16.75, 40);
  empregados[2] = new EmpregadoComissionado("Sarah", "Joaquina", "333-333-333.33", 9, 8, 1994, 10000, .06);
  empregados[3] = new EmpregadoComissionadoBase("Rony", "Texeira", "444-444-444.44", 3, 2, 1995, 5000, .04, 300);
  int mes = determinaMes();
  cout << "Empregados processados de forma polimorfica:\n";
  for (size_t i = 0; i < empregados.size(); i++)
  {
    empregados[i]->imprime();
    EmpregadoComissionadoBase *ptr = dynamic_cast<EmpregadoComissionadoBase*>(empregados[i]);
    if (ptr != 0)
    {
      double salarioAntigo = ptr->getSalarioBase();
      cout << " salario antigo: " << salarioAntigo << endl;
      ptr->setSalarioBase(1.10 * salarioAntigo);
      cout << "novo salario com 10% de aumento: " << ptr->getSalarioBase();
    }
    Data aniversario = empregados[i]->getDataNascimento();
    // se o mes atual eh aniversario do empregado, ele recebe um bonus de 100
    if (aniversario.getMes() == mes)
    {
      cout << "Feliz aniversário! Você ganhou " << (empregados[i]->salario() + 100.0) << endl;
    }
    else
    {
      cout << " Recebeu " << empregados[i]->salario() << endl;
    }
  }

  for (size_t j = 0; j < empregados.size(); j++)
  {
    cout << "deletando objeto " << typeid(*empregados[j]).name() << endl;
    delete empregados[j];
  }
  return 0;
}


