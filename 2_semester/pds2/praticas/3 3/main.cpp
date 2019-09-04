#include <iostream>
#include <iomanip>
#include <vector>
#include <typeinfo>
#include "Pacote.hpp"
#include "PacoteDoisDias.hpp"
#include "PacoteNoturno.hpp"

using std::vector;
using std::cout;
using std::endl;
using std::setprecision;
using std::fixed;

int main()
{

  vector<Pacote*> pacotes;

  // Ordem dos parametros no construtor:
  // Pacote(destinatarioNome, destinatarioEndereco, destinatarioCidade, destinatarioEstado,
  // destinatarioCEP, ... mesmas informacoes para remetente, peso, custo)

  pacotes.push_back(new Pacote( "Carlos Eduardo", "Quadra 3 978", "Águas Lindas de Goiás",
    "GO", 72922470, "Roberto Enrico", "Praça Nossa Senhora", "Recife", "PE", 50010913, 8.5, .5 ));



  // Ordem dos parametros no construtor:
  // PacoteDoisDias(mesmos parametros de Pacote, taxaFixa)
  pacotes.push_back(new PacoteDoisDias( "Igor Polina", "Rua Piauí",
  "Satélite", "PI", 64059460, "Joana Gabriela", "Rua Imbituba 5", "Porto Velho",
  "RO", 76808124, 10.5, 0.65, 2.0 ));


  // Ordem dos parametros no construtor:
  // PacoteNoturno(mesmos parametros de Pacote, taxaNoturna)
  pacotes.push_back(new PacoteNoturno( "Tiago Cláudio", "Rua Caetano Cosme", "Caruaru",
  "PE", 55019385, "Sebastião Lorenzo", "Rua Oscarina Marques", "Ji-Paraná", "RO", 76900757,
  12.25, .7, .25 ));

  double custoFreteTotal = 0.0;
  cout << fixed << setprecision( 2 );

  cout << pacotes[0]->calcularCusto() << endl;
  cout << pacotes[1]->calcularCusto() << endl;
  cout << pacotes[2]->calcularCusto() << endl;

  PacoteDoisDias *doisdias = dynamic_cast<PacoteDoisDias*>(pacotes[1]);
  if ( doisdias != 0 )
  {
    doisdias->setTaxaFixa(-15);
    doisdias->setDestinatarioNome("Carlim Dudu");
    doisdias->setDestinatarioEndereco("Quadra 3, n 978");
    doisdias->setDestinatarioEstado("Goiania");
    doisdias->setDestinatarioCidade("Agua Lindas de Goiania");
    doisdias->setDestinatarioCEP(72922470);
    doisdias->setPeso(10);
    cout << doisdias->getTaxaFixa() << endl;
  }
  cout << pacotes[1]->calcularCusto() << endl;

  PacoteNoturno *noturno = dynamic_cast<PacoteNoturno*>(pacotes[2]);
  if ( noturno != 0 )
  {
    cout << noturno->getTaxaNoturnaPorQuilo() << endl;
    noturno->setTaxaNoturnaPorQuilo(0.66);
    noturno->setRemetenteNome("Tiago Claudim");
    noturno->setRemetenteEndereco("Rua Caetano Cosme Damiao");
    noturno->setRemetenteEstado("Pernambuco");
    noturno->setRemetenteCidade("Cariri");
    noturno->setRemetenteCEP(55019386);
    noturno->setPeso(-10);
    cout << noturno->getTaxaNoturnaPorQuilo() << endl;
  }
  cout << pacotes[2]->calcularCusto() << endl;

  for (int i = 0; i < pacotes.size(); ++i)
  {

    cout << pacotes[i]->getRemetenteNome() << endl
      << pacotes[i]->getRemetenteEndereco() << endl
      << pacotes[i]->getRemetenteCidade() << endl
      << pacotes[i]->getRemetenteEstado() << endl
      << pacotes[i]->getRemetenteCEP() << endl;

    cout << pacotes[i]->getDestinatarioNome() << endl
      << pacotes[i]->getDestinatarioEndereco() << endl
      << pacotes[i]->getDestinatarioCidade() << endl
      << pacotes[i]->getDestinatarioEstado() << endl
      << pacotes[i]->getDestinatarioCEP() << endl;

    double custo = pacotes[i]->calcularCusto();
    cout << custo << endl;
    custoFreteTotal += custo;
  }
  cout << custoFreteTotal << endl;
  return 0;
}
