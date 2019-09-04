#include <exception>
#include <string>

using std::exception;
using std::string;

class ArquivoException : public exception {
	string diretorio;
	public:
		ArquivoException(string dir) : diretorio(dir) {}
		string getCaminhoArquivo() { return diretorio; }
		string getNomeArquivo() {
			return diretorio;
		} 
		string getPastaArquivo() {
			return diretorio;
		}
};

class AbrirArquivoException : public ArquivoException {
	public:
		AbrirArquivoException(string dir) : ArquivoException(dir) {}
		virtual const char* what() const throw () {
			return "Erro: ocorreu um erro ao tentar abrir o arquivo.";
		}
};

class CriarArquivoException : public ArquivoException {
	public:
		CriarArquivoException(string dir) : ArquivoException(dir) {}
		virtual const char* what() const throw () {
			return "Erro: ocorreu um erro ao tentar criar um novo arquivo.";
		}
};

class ArquivoVazioException : public ArquivoException {
	public:
		ArquivoVazioException(string dir) : ArquivoException(dir) {}
		virtual const char* what() const throw () {
			return "O arquivo está vazio.";
		}
};