#include <string>

#ifndef PACOTE_H
#define PACOTE_H

using namespace std;

class Pacote {
	protected:
		string nomeRemetente, enderecoRemetente, cidadeRemetente, estadoRemetente;
		string nomeDestinatario, enderecoDestinatario, cidadeDestinatario, estadoDestinatario;
		int cepRemetente, cepDestinatario;
		double peso, custoKG;

	public:
		Pacote(string nomeDestinatario, string enderecoDestinatario, string cidadeDestinatario, string estadoDestinatario, int cepDestinatario, string  nomeRemetente, string  enderecoRemetente, string  cidadeRemetente, string  estadoRemetente, int  cepRemetente, double peso, double custoKG);

		virtual ~Pacote();

		virtual double calcularCusto();

		int getDestinatarioCEP();
		void setDestinatarioCEP(int cepDestinatario);

		int getRemetenteCEP();
		void setRemetenteCEP(int cepRemetente);

		string getDestinatarioCidade();
		void setDestinatarioCidade(string cidadeDestinatario);

		string getRemetenteCidade();
		void setRemetenteCidade(string cidadeRemetente);

		double getCustoKg();
		void setCustoKg(double custoKg);

		string getDestinatarioEndereco();
		void setDestinatarioEndereco(string enderecoDestinatario);

		string getRemetenteEndereco();
		void setRemetenteEndereco(string enderecoRemetente);

		string getDestinatarioEstado();
		void setDestinatarioEstado(string estadoDestinatario);

		string getRemetenteEstado();
		void setRemetenteEstado(string estadoRemetente);

		string getDestinatarioNome();
		void setDestinatarioNome(string nomeDestinatario);

		string getRemetenteNome();
		void setRemetenteNome(string nomeRemetente);

		double getPeso();
		void setPeso(double peso);
};

#endif
