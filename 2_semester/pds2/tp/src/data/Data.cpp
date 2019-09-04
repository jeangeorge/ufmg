#include "../../include/data/Data.hpp"
#include<ctime>

// Inicializando o membro estatico que armazena a quantidade de dias de cada mes
const int Data::dias[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

Data::Data() {
	time_t t = time(0);  // Current time
	struct tm * now = localtime(&t);  // Localtime

	// struct tm: http://cplusplus.com/reference/clibrary/ctime/tm/
	int dia = now->tm_mday;
	int mes = now->tm_mon + 1;
	int ano = now->tm_year + 1900;

	setData(dia, mes, ano);
};

Data::Data(int dia, int mes, int ano) {
  	setData(dia, mes, ano);
}

void Data::setData(int dia, int mes, int ano) {
	if(!(mes >= 1 && mes <= 12)){
		throw DataInvalidaException();
		return;
	}

	if(!(ano >= 1900 && ano <= 2100)){
		throw DataInvalidaException();
		return;
	}

	// Testa se e um ano bissexto
	if (this->mes == 2 && anoBissexto(ano)) {
		if(!(dia >= 1 && dia <= 29)){
		throw DataInvalidaException();
		return;
		}
	} else {
		if(!(dia >= 1 && dia <= dias[mes])){
		throw DataInvalidaException();
		return;
		}
	}

	this->dia = dia;
	this->mes = mes;
	this->ano = ano;
}

int Data::getDia(){
	return this->dia;
}
int Data::getMesValor(){
	return this->mes;
}
int Data::getAno(){
	return this->ano;
}

// operador para incrementar uma data
Data &Data::operator++() {
  auxiliaIncremento();
  return *this;
}

// sobregarga do operador posfixo de incremento, note que o parametro inteiro nao tem um nome
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

// se o ano eh bissexto retorna true, caso contrario, falso
bool Data::anoBissexto(int testeAno) const {
  if (testeAno % 400 == 0 || (testeAno % 100 != 0 && testeAno % 4 == 0)) {
    return true;
  } else {
    return false;
  }
}

int Data::getMes() const {
  return mes;
}

// checa se o dia eh o ultimo dia do mes
bool Data::fimDoMes(int testeDia) const {
  if (mes == 2 && anoBissexto(ano)) {
    return testeDia == 29;  // se bissexto ultimo dia de fevereiro
  } else {
    return testeDia == dias[mes];
  }
}

// funcao para ajudar a incrementar a data
void Data::auxiliaIncremento() {
  // dia nao eh fim do mes
  if (!fimDoMes(dia)) {
    dia++;
  } else if (mes < 12)  // eh o fim do mes
      {
    mes++;
    dia = 1;
  } else  // ultimo dia do ano
  {
    ano++;
    mes = 1;
    dia = 1;
  }
}

// sobrecarga do operador de saida
ostream &operator<<(ostream &saida, const Data &d) {
	std::string nomeMes[13] = { "", "Janeiro", "Fevereiro", "Marco", "Abril",
			"Maio", "Junho", "Julho", "Agosto", "Setembro", "Outubro", "Novembro",
			"Dezembro" };
	saida << nomeMes[d.mes] << ' ' << d.dia << ", " << d.ano;
	return saida;
}
