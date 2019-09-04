#ifndef CRIATURA_HPP
#define CRIATURA_HPP

#include <string>

#include "Dado.hpp"

using std::string;

class Criatura {
	public:
		static const int FORCA_MINIMA = 1;

		Criatura(string _nome, int _armadura, int _forca);
		virtual ~Criatura();

		virtual int getArmadura();

		virtual int getForca();
		virtual void setForca(int);

		virtual string getNome();
		virtual void setNome(string);

		virtual int defender() = 0;
		virtual int atacar() = 0;

	protected:
		string nome;
		int armadura;
		int forca;
};

#endif
