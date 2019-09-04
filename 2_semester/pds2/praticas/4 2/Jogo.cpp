#include "Jogo.hpp"

Jogo::Jogo() {
  this->criatura1 = nullptr;
  this->criatura2 = nullptr;
  this->vencedor = nullptr;

  srand(12345);
}

Jogo::~Jogo() {}

void Jogo::jogar() {
  Criatura* atacante;
  Criatura* defensor;

  int aleatorio = rand();  // troca as posicoes metade das vezes
  int rounds = 1; // define o número de rounds

  if (aleatorio % 2 == 0) {
    atacante = this->criatura2;
    defensor = this->criatura1;
  } else {
    atacante = this->criatura1;
    defensor = this->criatura2;
  }

  // Enquanto não tem vencedor
  while (!vencedor) {
    cout << "####### Round " << rounds << " #######\n";
    turno(atacante, defensor);

    // checa se houve um vencedor nesse round
    if (!vencedor) {
      turno(defensor, atacante);
    }
    ++rounds;
  }


  // Mostra o vencedor quando sair do loop
  imprimeVencedor();
}

void Jogo::testaJogo() {
  criatura1 = new Vampiro();
  criatura2 = new Barbaro();
  jogar();


 /* criatura1 = new Medusa();
  criatura2 = new Mago();
  jogar();
  desalocaCriaturas();*/
}

void Jogo::turno(Criatura *atacante, Criatura *defensor) {
  // valor de ataque e defesa de cada um
  int ataquePts = atacante->atacar();
  int defesaPts = defensor->defender();

  // forca inicial
  cout << atacante->getNome() << " atacante: " << atacante->getForca() << endl;
  cout << defensor->getNome() << " defensor: " << defensor->getForca() << endl;

  // poder especial do charme do vampiro
  if (defesaPts == Vampiro::CHARME_DO_VAMPIRO) {
    cout << defensor->getNome() << " evitou que " << atacante->getNome() << " atacasse.\n";
  }
  // olhar da medusa
  else if (ataquePts == Medusa::OLHAR_DA_MEDUSA) {
    cout << atacante->getNome() << " usou o olhar! " << defensor->getNome() << " virou pedra!\n";
    defensor->setForca(0);
  }
  // round normal, sem poder especial e olhar da medusa
  else{
  	// Calcula o dano e a perda
  	int dano = ataquePts - defesaPts;
		int perda = dano - defensor->getArmadura();

		cout << atacante->getNome() << " atacou com " << ataquePts << endl;
		cout << defensor->getNome() << " defendeu com " << defesaPts << endl;

		cout << dano << " de dano infligido na armadura\n";

		// Se houve perda
		if (perda > 0) {
			defensor->setForca(defensor->getForca() - perda);
			cout << defensor->getNome() << " está com " << defensor->getForca() << " de força\n";
		} else {
			cout << "Sem perda de força" << endl;
		}
  }


  if (defensor->getForca() < Criatura::FORCA_MINIMA) {
    // o atacante venceu! atribuimos ele a vencedor
  	this->vencedor = atacante;
  }
}

void Jogo::imprimeVencedor() {
  cout << criatura1->getNome() << ": " << criatura1->getForca() << "\n";
  cout << criatura2->getNome() << ": " << criatura2->getForca() << "\n";
  cout << vencedor->getNome() << " venceu!\n";
}


void Jogo::desalocaCriaturas() {
  criatura1 = nullptr;
  criatura2 = nullptr;
  vencedor = nullptr;

  delete criatura1;
  delete criatura2;
  delete vencedor;
}
