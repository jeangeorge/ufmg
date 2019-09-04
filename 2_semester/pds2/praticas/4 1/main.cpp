#include <iostream>
#include <iomanip>
#include <vector>
#include <typeinfo>
#include <ctime>
#include <cstdlib>

#include "Empregado.hpp"
#include "EmpregadoSalariado.hpp"
#include "EmpregadoPorHora.hpp"
#include "EmpregadoComissionado.hpp"
#include "EmpregadoComissionadoBase.hpp"
#include "Data.hpp"

using namespace std;

// retorna o mes corrente
int determinaMes() {
  time_t tempoAtual;
  char stringMes[3];

  time(&tempoAtual);
  strftime(stringMes, 3, "%m", localtime(&tempoAtual));

  return atoi(stringMes);
}

int main() {
 /* cout << fixed << setprecision(2);
  vector<Empregado *> empregados(4);
  int mes = determinaMes();

  empregados[0] = new EmpregadoSalariado("Joao", "Mario", "111-111-111.11", 5, 15, 1994, 800);
  empregados[1] = new EmpregadoPorHora("Karen", "Ferreira", "222-222-222.22", 11, 29, 1999, 16.75, 40);
  empregados[2] = new EmpregadoComissionado("Sarah", "Joaquina", "333-333-333.33", 8, 8, 1994, 10000, .06);
  empregados[3] = new EmpregadoComissionadoBase("Rony", "Texeira", "444-444-444.44", 2, 2, 1995, 5000, 0.04, 300.0);

  cout << "Empregados processados de forma polimorfica:\n";
  for (unsigned int i = 0; i < empregados.size(); i++) {
    EmpregadoComissionadoBase *ptr = dynamic_cast<EmpregadoComissionadoBase *>(empregados[i]);
    Data aniversario = empregados[i]->getDataNascimento();

    empregados[i]->imprime();

    // se for um EmpregadoComissionadoBase ele recebe um bonus
    if (ptr != 0) {
    	double salarioAntigo = ptr->getSalarioBase();
      cout << " salario antigo: " << salarioAntigo << endl;
      ptr->setSalarioBase(1.10 * salarioAntigo);
      cout << "novo salario com 10% de aumento: " << ptr->getSalarioBase();
    }

    // se o mes atual eh aniversario do empregado, ele recebe um bonus de 100
    if (aniversario.getMes() == mes) {
      cout << "Feliz aniversário! Você recebeu " << (empregados[i]->salario() + 100.0) << endl;
    } else {
      cout << " Recebeu " << empregados[i]->salario() << endl;
    }
  }

  for (unsigned int j = 0; j < empregados.size(); j++) {
    cout << "deletando objeto " << typeid(*empregados[j]).name() << endl;
    delete empregados[j];
  }
*/
  EmpregadoComissionadoBase empregado("Nome","Sobrenome","12345678920",1,1,2002,500.0,0.5,-300);
  /*cout << empregado.getSalarioBase() << endl;
  cout << empregado.salario() << endl;*/

  EmpregadoComissionado empregado2("Nome","Sobrenome","12345678920",1,1,2000,1500.0,0.5);
  /*cout << empregado2.getTaxaComissao() << endl;
  cout << empregado2.getVendasBrutas() << endl;
  cout << empregado2.salario() << endl;*/

  EmpregadoPorHora empregado3("Nome","Sobrenome","12345678920",1,1,2000,20.0,40);
  EmpregadoPorHora empregado4("Nome","Sobrenome","12345678920",1,1,2001,20.0,45);
  /*cout << empregado3.salario() << endl;
  cout << empregado4.salario() << endl;*/

  EmpregadoSalariado empregado5("Nome","Sobrenome","12345678920",1,1,2000,957);
  cout << empregado5.getDataNascimento() << endl;
  return 0;
}
