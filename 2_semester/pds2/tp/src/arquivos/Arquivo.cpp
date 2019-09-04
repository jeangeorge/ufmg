#include "../../include/arquivos/Arquivo.hpp"

Arquivo::Arquivo(string nome) {
	this->diretorio = "./src/arquivos/" + nome;
	try {
		abrirModoLeitura();
	} catch (AbrirArquivoException& e) {
		throw;
	}
}

Arquivo::~Arquivo() {
	fecharModoLeitura();
	fecharModoEscrita();
}

void Arquivo::abrirModoLeitura() {
	arquivoLeitura.open(diretorio, ios::in);

	if (!arquivoLeitura.is_open()) {
		throw AbrirArquivoException(diretorio);
	}
}

void Arquivo::abrirModoEscrita() {
	arquivoEscrita.open(diretorio);

	if (!arquivoEscrita.is_open()) {
		throw AbrirArquivoException(diretorio);
	}
}

void Arquivo::fecharModoEscrita() {
	arquivoEscrita.close();
}

void Arquivo::fecharModoLeitura() {
	arquivoLeitura.close();
	arquivoEscrita.close();
}

void Arquivo::atualizarDados(const vector<Bibliotecario>& vectorBibliotecarios) {
	abrirModoEscrita();
	for(auto bibliotecarios : vectorBibliotecarios)
		this->arquivoEscrita << bibliotecarios.toStringToSave();
	fecharModoEscrita();
}

void Arquivo::atualizarDados(const vector<Usuario>& vectorUsuarios) {
	abrirModoEscrita();
	for(auto usuarios : vectorUsuarios)
		this->arquivoEscrita << usuarios.toStringToSave();
	fecharModoEscrita();
}

void Arquivo::atualizarDados(const vector<Emprestimo>& vectorEmprestimos) {
	abrirModoEscrita();
	for(auto emprestimos : vectorEmprestimos)
		this->arquivoEscrita << emprestimos.toStringToSave();
	fecharModoEscrita();
}

void Arquivo::atualizarDados(const vector<Livro>& vectorLivros) {
	abrirModoEscrita();
	for(auto livros : vectorLivros)
		this->arquivoEscrita << livros.toStringToSave();
	fecharModoEscrita();
}

void Arquivo::atualizarDados(const vector<Reserva>& vectorReservas) {
	abrirModoEscrita();
	for(auto reservas : vectorReservas)
		this->arquivoEscrita << reservas.toStringToSave();
	fecharModoEscrita();
}

void Arquivo::alocarDadosLinha(string linha, vector<Bibliotecario>& vectorBibliotecarios) {
	int j = 0;
	istringstream ss(linha);
	string atributo, dados[8]; //id, login, senha, nome, sobrenome, cpf, sexo, dataNascimento

	// Capturar cada valor dentro da linha (delimitado por ;) e coloca no array
	while (getline(ss, atributo, ';')) {
		dados[j] = atributo;
		j++;
	}
	Bibliotecario bibliotecario(atoi(dados[0].c_str()), dados[1], dados[2],
			dados[3], dados[4], dados[5], dados[6][0], dados[7]);

	vectorBibliotecarios.push_back(bibliotecario);
}

void Arquivo::alocarDadosLinha(string linha, vector<Usuario>& vectorUsuarios) {
	int j = 0;
	istringstream ss(linha);
	string atributo, dados[10]; // id, nome, sobrenome, cpf, sexo, dataNascimento, email, telefone, permissaoAlugar, diasBloqueado

	// Captura cada valor dentro da linha (delimitado por ;) e coloca no array
	while (getline(ss, atributo, ';')) {
		dados[j] = atributo;
		j++;
	}
	Usuario usuario(atoi(dados[0].c_str()), dados[1], dados[2], dados[3],
			dados[4][0], dados[5], dados[6], dados[7], atoi(dados[8].c_str()));

	vectorUsuarios.push_back(usuario);
}

void Arquivo::alocarDadosLinha(string linha,
		vector<Emprestimo>& vectorEmprestimos) {
	int j = 0;
	istringstream ss(linha);
	string atributo, dados[10]; //idEmprestimo, idUsuario, idLivro, diaAluguel, mesAluguel, anoAluguel, multa
	// Captura cada valor dentro da linha (delimitado por ;) e coloca no array
	while (getline(ss, atributo, ';')) {
		dados[j] = atributo;
		j++;
	}
	Emprestimo emprestimo(atoi(dados[0].c_str()), atoi(dados[1].c_str()), atoi(dados[2].c_str()), atoi(dados[3].c_str()), atoi(dados[4].c_str()),  atoi(dados[5].c_str()), atoi(dados[9].c_str()));
	vectorEmprestimos.push_back(emprestimo);

}

void Arquivo::alocarDadosLinha(string linha, vector<Livro>& vectorLivros) {
	int j = 0;
	istringstream ss(linha);
	string atributo, dados[5]; //id, titulo, autor, genero, quantideDeCopias

	// Captura cada valor dentro da linha (delimitado por ;) e coloca no array
	while (getline(ss, atributo, ';')) {
		dados[j] = atributo;
		j++;
	}
	Livro livro(atoi(dados[0].c_str()), dados[1], dados[2], dados[3],
			atoi(dados[4].c_str()));

	vectorLivros.push_back(livro);
}

void Arquivo::alocarDadosLinha(string linha, vector<Reserva>& vectorReservas) {
	int j = 0;
	istringstream ss(linha);
	string atributo, dados[3]; //id, id do usuario, id do livro

	// Captura cada valor dentro da linha (delimitado por ;) e coloca no array
	while (getline(ss, atributo, ';')) {
		dados[j] = atributo;
		j++;
	}
	Reserva reserva(atoi(dados[0].c_str()), atoi(dados[1].c_str()), atoi(dados[2].c_str()));

	vectorReservas.push_back(reserva);
}
