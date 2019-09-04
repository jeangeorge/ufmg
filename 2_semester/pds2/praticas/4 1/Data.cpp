#include "Data.hpp"

// initialize o membro estÃ¡tico que armazena a quantidade de dias de cada mes
const int Data::dias[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

Data::Data(int m, int d, int a) { setData(m, d, a); }

int Data::getMes() const { return mes; }

void Data::setData(int mm, int dd, int aa) {
  mes = (mm >= 1 && mm <= 12) ? mm : 1;
  ano = (aa >= 1900 && aa <= 2100) ? aa : 1900;

  // testa se eh um ano bissexto
  if (mes == 2 && anoBissexto(ano)) {
    dia = (dd >= 1 && dd <= 29) ? dd : 1;
  } else {
    dia = (dd >= 1 && dd <= dias[mes]) ? dd : 1;
  }
}

// checa se o dia eh o ultimo dia do mes
bool Data::fimDoMes(int testeDia) const {
  if (mes == 2 && anoBissexto(ano)) {
    return testeDia == 29;  // se bissexto ultimo dia de fevereiro
  } else {
    return testeDia == dias[mes];
  }
}

// se o ano eh bissexto retorna true, caso contrario, falso
bool Data::anoBissexto(int testeAno) const {
  if (testeAno % 400 == 0 || (testeAno % 100 != 0 && testeAno % 4 == 0)) {
    return true;
  } else {
    return false;
  }
}

// operador para incrementar uma data
Data &Data::operator++() {
  auxiliaIncremento();
  return *this;
}

// sobregarga do operador posfixo de incremento, note que o parametro inteiro
// nao tem um nome
Data Data::operator++(int) {
  Data temp = *this;
  auxiliaIncremento();

  // retorna o valor temporario nao incrementado
  return temp;
}

// adiciona um numero de dias especifico a data
const Data &Data::operator+=(int diasAdicionais) {
  for (int i = 0; i < diasAdicionais; i++) {
    auxiliaIncremento();
  }

  return *this;
}

// funcao para ajudar a incrementar a data
void Data::auxiliaIncremento() {
  // dia nao eh fim do mes
  if (!fimDoMes(dia)) {
    dia++;
  }
  // eh o fim do mes
  else if (mes < 12) {
    mes++;
    dia = 1;
  }
  // ultimo dia do ano
  else {
    ano++;
    mes = 1;
    dia = 1;
  }
}

// sobrecarga do operador de saida
ostream &operator<<(ostream &saida, const Data &d) {
  static std::string nomeMes[13] = {
      "",        "Janeiro",  "Fevereiro", "Março", "Abril",
      "Maio",    "Junho",    "Julho",     "Agosto", "Setembro",
      "Outubro", "Novembro", "Dezembro"};

  saida << nomeMes[d.mes + 1] << ' ' << d.dia << ", " << d.ano;

  return saida;
}
