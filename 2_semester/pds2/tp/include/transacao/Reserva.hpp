#ifndef RESERVA_H
#define RESERVA_H

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

using std::cout;
using std::endl;
using std::string;
using std::stringstream;

class Reserva {
	public:
		Reserva(int idReserva, int idUsuario, int idLivro);
		~Reserva();

		string toString();
		string toStringToSave();

		int getIdLivro();
		void setIdLivro(int idLivro);

		int getIdUsuario();
		void setIdUsuario(int idUsuario);

		int getIdReserva();
		void setIdReserva(int idReserva);

		// string getDataPrevista();
		// void setDataPrevista(string dataPrevista);

	private:
		int idReserva, idUsuario, idLivro;
		string dataPrevista;
};

#endif
