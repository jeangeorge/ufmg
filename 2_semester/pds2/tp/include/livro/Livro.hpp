#ifndef LIVRO_H
#define LIVRO_H

#include <sstream>
#include <string>

using std::string;
using std::stringstream;

class Livro {
	public:
		Livro(int id, string titulo, string autor, string genero,
			int quantidadeDeCopias);

		void aumentarQuantidade();
		string toString();
		string toStringToSave();

	 	string getAutor();
		void setAutor(string autor);

	 	string getGenero();
		void setGenero(string genero);

		int getId();
		void setId(int id);

		int getQuantidadeDeCopias();
		void setQuantidadeDeCopias(int quantidadeDeCopias);

	 	string getTitulo();
		void setTitulo(string titulo);

	private:
		int id;
		string titulo, autor, genero;
		int quantidadeDeCopias;
};

#endif
