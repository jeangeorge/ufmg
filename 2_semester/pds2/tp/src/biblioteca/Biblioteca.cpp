#include "../../include/biblioteca/Biblioteca.hpp"

/*
Construtor - define as variaveis necessarias e comeca a iniciar o sistema

@param nome string que representa o nome da biblioteca
@param endereco string que representa o endereco da biblioteca
@param telefone string que representa o telefone da biblioteca
*/
Biblioteca::Biblioteca(string nome, string endereco, string telefone) :
		nome(nome), endereco(endereco), telefone(telefone) {
	this->bibliotecarioAtual = new Bibliotecario();
	this->iniciarSistema();
}

/*
Iniciar sistema - tenta carregar os arquivos necessarios para iniciar o sistema, receber
os dados do bibliotecario para efetuar o login, e exibir o menu de operacoes
*/
void Biblioteca::iniciarSistema() {
	try {
		if(!this->carregarArquivos())
			return;

		if(!(this->bibliotecarioAtual->logarNoSistema(this->vectorBibliotecarios))) {
			cout << "Finalizando Sistema...";
			return;
		}

		this->telaAtual = new TelaPrincipal();

		this->exibirConfirmacaoLogin();
		this->exibirMenu();

		cout << "Finalizando Sistema...";
	} catch (AbrirArquivoException &e) {
		cout << "Ocorreu um erro ao tentar carregar os arquivos do sistema." << endl;
	}
}

/*
Carregar arquivos - tenta ler os arquivos txt e carregar os dados na memoria (em vectors)
*/
bool Biblioteca::carregarArquivos() {
	try {
		this->arquivoBibliotecarios = new Arquivo("bibliotecarios.txt");
		this->arquivoUsuarios = new Arquivo("usuarios.txt");
		this->arquivoLivros = new Arquivo("livros.txt");
		this->arquivoEmprestimos = new Arquivo("emprestimos.txt");
		this->arquivoReservas = new Arquivo("reservas.txt");

		this->arquivoBibliotecarios->obterDados(this->vectorBibliotecarios);
		this->arquivoUsuarios->obterDados(this->vectorUsuarios);
		this->arquivoLivros->obterDados(this->vectorLivros);
		this->arquivoEmprestimos->obterDados(this->vectorEmprestimos);
		this->arquivoReservas->obterDados(this->vectorReservas);

		if(this->vectorBibliotecarios.empty() || this->vectorUsuarios.empty())
			return false;
		
		return true;
	} catch (AbrirArquivoException &e) {
		throw;
	}
}

/*
Retorna o nome da biblioteca

@return Nome da biblioteca
*/
string Biblioteca::getNome() {
	return this->nome;
}

/*
Retorna o endereco da biblioteca

@return Endereco da biblioteca
*/
string Biblioteca::getEndereco() {
	return this->endereco;
}

/*
Retorna o telefone da biblioteca

@return Telefone da biblioteca
*/
string Biblioteca::getTelefone() {
	return this->telefone;
}

/*
Define um novo nome para a biblioteca

@param novoNome string com o novo nome da biblioteca
*/
void Biblioteca::setNome(string novoNome) {
	this->nome = novoNome;
}

/*
Define um novo endereco para a biblioteca

@param novoEndereco string com o novo endereco da biblioteca
*/
void Biblioteca::setEndereco(string novoEndereco) {
	this->endereco = novoEndereco;
}

/*
Define um novo telefone para a biblioteca

@param novoTelefone string com o novo telefone da biblioteca
*/
void Biblioteca::setTelefone(string novoTelefone) {
	this->telefone = novoTelefone;
}

/*
Destrutor - apaga o espaco de memoria alocado durante a execucao para
as variaveis necessarias
*/
Biblioteca::~Biblioteca() {
	delete this->arquivoEmprestimos;
	delete this->arquivoLivros;
	delete this->arquivoUsuarios;
	delete this->arquivoBibliotecarios;
	delete this->arquivoReservas;
	delete this->bibliotecarioAtual;
	delete this->telaAtual;
}

/*
Listar Livros - exibe uma lista com todos os livros e seus dados
*/
void Biblioteca::listarLivros() {
	cout << "\nLivros:" << endl;
	for(auto livro : this->vectorLivros)
		cout << livro.toString() << endl;
}

/*
Pesquisar Livro - pesquisa e exibe, se encontrado, um livro
com titulo informado pelo bibliotecario
*/
void Biblioteca::pesquisarLivro() {
	string nome, tituloAtual;
	int contador = 0;
	cout << "\nDigite o titulo do Livro desejado (ou digite ':C' para cancelar):" << endl;
	if(!this->getEntradaValida(nome, true))
		return;
	transform(nome.begin(), nome.end(), nome.begin(), ::tolower);
	for(auto livro : this->vectorLivros) {
		tituloAtual = livro.getTitulo();
		transform(tituloAtual.begin(), tituloAtual.end(), tituloAtual.begin(), ::tolower);
		if(tituloAtual == nome) {
			cout << livro.toString() << endl;
			contador++;
		}
	}
	if(contador == 0)
		cout << "Nao ha nenhum livro cadastrado com esse titulo" << endl;
}

/*
Atualizar Livro - recebe entrada, pesquisa um livro e, se encontrado, salva
seus dados de acordo com as entradas informadas pelo bibliotecario
*/
void Biblioteca::atualizarLivro() {
	string *dados = new string[3];
	int idLivro, qtdCopias = 0;
	cout << "\nDigite o ID do Livro a ser atualizado (ou digite ':C' para cancelar):" << endl;
	if(!this->getEntradaInt(idLivro))
		return;
	for(auto &livro : this->vectorLivros) {
		if(livro.getId() == idLivro) {
			cout << "Atualize as informacoes do Livro de ID " << livro.getId() <<
					"\nDeixe o campo em branco para manter o valor atual" << endl;
			if(!this->obterDadosAtualizarLivro(livro))
				return;

			this->arquivoLivros->atualizarDados(this->vectorLivros);
			cout << "O livro foi atualizado" << endl;
			return;
		}
	}
	cout << "Nao ha livro cadastrado com esse ID" << endl;
}

/*
Obter dados para atualizar livro - recebe as entradas do bibliotecario para
definir os dados do livro a ser atualizado. Se a entrada for vazia, mantem
o valor antigo

@see atualizarLivro

@param l Livro a ser atualizado
@return true, se os dados informados sao validos e o livro foi atualizado
@return false, se o processo de atualizacao foi cancelado
*/
bool Biblioteca::obterDadosAtualizarLivro(Livro& l) {
	int qtdCopias;
	string dados[3];
	
	cout << "Titulo (" << l.getTitulo() << "): " << endl;
	if(!this->getEntradaValida(dados[0], false))
		return false;

	cout << "Autor (" << l.getAutor() << "): " << endl;
	if(!this->getEntradaValida(dados[1], false))
		return false;

	cout << "Genero (" << l.getGenero() << "): " << endl;
	if(!this->getEntradaValida(dados[2], false))
		return false;

	cout << "Quantidade de Copias (" << l.getQuantidadeDeCopias() << "): " << endl;
	if(!this->getEntradaInt(qtdCopias))
		return false;

	if(!dados[0].empty())
		l.setTitulo(dados[0]);

	if(!dados[1].empty())
		l.setAutor(dados[1]);

	if(!dados[2].empty())
		l.setGenero(dados[2]);

	l.setQuantidadeDeCopias(qtdCopias);
	return true;
}

/*
Adicionar Livro - adiciona um novo livro e salva
*/
void Biblioteca::adicionarLivro() {
	Livro* livro;
	
	cout << "\nDigite os dados do Livro (ou digite ':C' para cancelar):" << endl;
	if(!this->construirNovoLivro(livro))
		return;

	if(!this->confirmarAcao("Salvar livro?\n")) {
		delete livro;
		return;
	}

	this->vectorLivros.push_back(*livro);
	this->arquivoLivros->atualizarDados(this->vectorLivros);
	cout << "Livro adicionado com sucesso" << endl;
}

/*
Construir Novo Livro - recebe entradas e tenta criar um novo livro

@see adicionarLivro

@param l ponteiro de Livro passado por referencia

@return true, se os dados informados sao validos e o livro foi criado
@return false, se o processo de criacao foi cancelado ou ja existe um livro igual
*/
bool Biblioteca::construirNovoLivro(Livro*& l) {
	string dados[3];
	int qtdCopias = 0;
	cout << "Titulo: " << endl;
	if(!this->getEntradaValida(dados[0], true))
		return false;
	cout << "Autor: " << endl;
	if(!this->getEntradaValida(dados[1], true))
		return false;
	cout << "Genero: " << endl;
	if(!this->getEntradaValida(dados[2], true))
		return false;
	cout << "Quantidade de Copias: " << endl;
	if(!this->getEntradaInt(qtdCopias))
		return false;
	
	if(this->existeLivro(dados[0], dados[1])) {
		cout << "Livro ja cadastrado" << endl;
		return false;
	}

	l = new Livro(this->getIdNovoLivro(), dados[0], dados[1], dados[2], qtdCopias);
	return true;
}

/*
Existe Livro - verifica se existe um livro com determinado titulo e autor

@see construirNovoLivro

@param titulo string contendo o titulo do livro a ser comparado
@param autor string contendo o autor do livro a ser comparado

@return true, se existe um livro
@return false, se nao existe um livro
*/
bool Biblioteca::existeLivro(string titulo, string autor) {
	string tituloAtual, autorAtual;
	transform(titulo.begin(), titulo.end(), titulo.begin(), ::tolower);
	transform(autor.begin(), autor.end(), autor.begin(), ::tolower);
	for(auto livro : this->vectorLivros) {
		tituloAtual = livro.getTitulo();
		tituloAtual = livro.getAutor();
		transform(tituloAtual.begin(), tituloAtual.end(), tituloAtual.begin(), ::tolower);
		transform(autorAtual.begin(), autorAtual.end(), autorAtual.begin(), ::tolower);

		if((titulo == tituloAtual) && (autor == autorAtual))
			return true;
	}
	return false;
}

/*
Existe Livro - verifica se existe um livro com determinado ID

@see renovarEmprestimo

@param idLivro int contendo o ID do livro a ser pesquisado

@return ponteiro para o livro, se existe um livro
@return nullptr, se nao existe um livro
*/
Livro* Biblioteca::existeLivro(int idLivro) {
	for(auto &livro : this->vectorLivros) {
		if(livro.getId() == idLivro)
			return &livro;
	}
	return nullptr;
}

/*
Remover Livro - remove um livro com ID (inteiro) informado pelo bibliotecario e salva
*/
void Biblioteca::removerLivro() {
	int idLivro, posicaoLivro = 0;

	cout << "\nDigite a ID do Livro que deseja remover (ou digite ':C' para cancelar):" << endl;
	if(!this->getEntradaInt(idLivro))
		return;

	for(auto livro : this->vectorLivros) {

		if(livro.getId() == idLivro) {
			if(!this->confirmarAcao("Tem certeza que deseja excluir o livro?\n"))
				return;
			this->vectorLivros.erase(this->vectorLivros.begin() + posicaoLivro);
			this->arquivoLivros->atualizarDados(this->vectorLivros);
			cout << "Livro removido com sucesso" << endl;
			return;
		}
		posicaoLivro++;
	}
	cout << "Nao ha livro com esse ID" << endl;
}

/*
Listar Usuarios - exibe uma lista com todos os usuarios e seus dados
*/
void Biblioteca::listarUsuarios() {
	cout << "\nUsuarios:" << endl;
	for(auto usuario : this->vectorUsuarios)
		cout << usuario.toString() << endl;
}

/*
Pesquisar Usuario - pesquisa e exibe, se encontrado, um usuario
com CPF (apenas numeros) informado pelo bibliotecario
*/
void Biblioteca::pesquisarUsuario() {
	string cpf;
	cout << "\nDigite o CPF do Usuario desejado (ou digite ':C' para cancelar):" << endl;
	if(!Usuario::getCpfValido(cpf, true))
		return;
	for(auto usuario : this->vectorUsuarios) {
		if(usuario.getCpf() == cpf) {
			cout << usuario.toString() << endl;
			return;
		}
	}
	cout << "Nao ha Usuario cadastrado com esse CPF." << endl;
}

/*
Atualizar Usuario - recebe entrada, pesquisa um usuario e, se encontrado, salva
seus dados de acordo com as entradas informadas pelo bibliotecario
*/
void Biblioteca::atualizarUsuario() {
	string *dados = new string[8];
	int idUsuario;
	cout << "\nDigite o ID do Usuario a ser atualizado (ou digite ':C' para cancelar):" << endl;
	if(!this->getEntradaInt(idUsuario))
		return;
	for(auto &usuario : this->vectorUsuarios) {
		if(usuario.getId() == idUsuario) {
			cout << "Atualize as informacoes do Usuario de ID " << usuario.getId() <<
					"\nDeixe o campo em branco para manter o valor atual" << endl;
			if(!this->obterDadosAtualizarUsuario(usuario))
				return;

			this->arquivoUsuarios->atualizarDados(this->vectorUsuarios);
			cout << "O usuario foi atualizado" << endl;
			return;
		}
	}
	cout << "Nao ha Usuario cadastrado com esse ID" << endl;
}

/*
Obter dados para atualizar usuario - recebe as entradas do bibliotecario para
definir os dados do usuario a ser atualizado. Se a entrada for vazia, mantem
o valor antigo

@see atualizarUsuario

@param u usuario a ser atualizado
@return true, se os dados informados sao validos e o usuario foi atualizado
@return false, se o processo de atualizacao foi cancelado
*/
bool Biblioteca::obterDadosAtualizarUsuario(Usuario& u) {
	string dados[8];

	cout << "Nome (" << u.getNome() << "): " << endl;
	if(!this->getEntradaValida(dados[0], false))
		return false;

	cout << "Sobrenome (" << u.getSobrenome() << "): " << endl;
	if(!this->getEntradaValida(dados[1], false))
		return false;

	cout << "CPF (" << u.getCpf() << "): " << endl;
	if(!Usuario::getCpfValido(dados[2], false))
		return false;

	cout << "Sexo (" << u.getSexo() << "): " << endl;
	if(!Usuario::getSexoValido(dados[3]))
		return false;

	cout << "Data de Nascimento (" << u.getDataNascimento() << "): " << endl;
	getline(cin, dados[4]);

	cout << "Email (" << u.getEmail() << "): " << endl;
	getline(cin, dados[5]);

	cout << "Telefone (" << u.getTelefone() << "): " << endl;
	getline(cin, dados[6]);

	cout << "Status (" << u.getStatus() << "): " << endl;
	if(!Usuario::getStatusValido(dados[7]))
		return false;

	this->verificarDefinirDadosUsuario(u, dados);
	return true;
}

/*
Verificar e definir dados do usuario - verifica se cada dado e' vazio, se for vazio
nao atualiza o atributo, se nao for vazio atualiza o atributo

@see obterDadosAtualizarUsuario

@param u usuario a ser atualizado passado por referencia
@param dados dados do usuario a serem checados
*/
void Biblioteca::verificarDefinirDadosUsuario(Usuario& u, string dados[8]) {
	if(!dados[0].empty())
		u.setNome(dados[0]);

	if(!dados[1].empty())
		u.setSobrenome(dados[1]);

	if(!dados[2].empty())
		u.setCpf(dados[2]);

	if(!dados[3].empty())
		u.setSexo(dados[3][0]);

	if(!dados[4].empty())
		u.setDataNascimento(dados[4]);

	if(!dados[5].empty())
		u.setEmail(dados[5]);

	if(!dados[6].empty())
		u.setTelefone(dados[6]);

	if(!dados[7].empty())
		u.setStatus(atoi(dados[7].c_str()));
}

/*
Adicionar Usuario - adiciona um novo usuario e salva
*/
void Biblioteca::adicionarUsuario() {
	Usuario* usuario;

	cout << "\nDigite os dados do Usuario (ou digite ':C' para cancelar):" << endl;
	if(!this->construirNovoUsuario(usuario))
		return;

	if(!this->confirmarAcao("Salvar usuario?\n")) {
		delete usuario;
		return;
	}

	this->vectorUsuarios.push_back(*usuario);
	this->arquivoUsuarios->atualizarDados(this->vectorUsuarios);
	cout << "O usuario foi adicionado com sucesso" << endl;
}

/*
Construir Novo Usuario - recebe entradas e tenta criar um novo usuario

@see adicionarUsuario

@param u ponteiro de Usuario passado por referencia

@return true, se os dados informados sao validos e o usuario foi criado
@return false, se o processo de criacao foi cancelado ou ja existe um usuario igual
*/
bool Biblioteca::construirNovoUsuario(Usuario*& u) {
	string dados[7];

	cout << "Nome: " << endl;
	if(!this->getEntradaValida(dados[0], true))
		return false;

	cout << "Sobrenome: " << endl;
	if(!this->getEntradaValida(dados[1], true))
		return false;

	cout << "CPF: " << endl;
	if(!Usuario::getCpfValido(dados[2], true))
		return false;

	cout << "Sexo: " << endl;
	if(!Usuario::getSexoValido(dados[3]))
		return false;

	cout << "Data de Nascimento: " << endl;
	getline(cin, dados[4]);

	cout << "Email: " << endl;
	getline(cin, dados[5]);

	cout << "Telefone: " << endl;
	getline(cin, dados[6]);

	if(this->existeUsuario(dados[2])) {
		cout << "Usuario ja cadastrado" << endl;
		return false;
	}

	u = new Usuario(this->getIdNovoUsuario(), dados[0], dados[1], dados[2],
			dados[3][0], dados[4], dados[5], dados[6], 1);
	return true;
}

/*
Existe Usuario - verifica se existe um usuario com determinado CPF

@see construirNovoUsuario

@param cpf string contendo o cpf do usuario a ser comparado

@return true, se existe um usuario
@return false, se nao existe um usuario
*/
bool Biblioteca::existeUsuario(string cpf) {
	for(auto usuario : this->vectorUsuarios) {
		if(cpf == usuario.getCpf()) {
			return true;
		}
	}
	return false;
}

/*
Existe Usuario - verifica se existe um usuario com determinado ID

@see renovarEmprestimo

@param idUsuario int contendo o ID do usuario a ser comparado

@return true, se existe um usuario
@return false, se nao existe um usuario
*/
Usuario* Biblioteca::existeUsuario(int idUsuario) {
	for(auto &usuario : this->vectorUsuarios) {
		if(idUsuario == usuario.getId()) {
			return &usuario;
		}
	}
	return nullptr;
}

/*
Remover Usuario - remove um usuario com ID (inteiro) informado pelo bibliotecario e salva
*/
void Biblioteca::removerUsuario() {
	int idUsuario, posicaoUsuario = 0, encontrouUsuario = 0;

	cout << "\nDigite a ID do Usuario que deseja remover (ou digite ':C' para cancelar):" << endl;
	if(!this->getEntradaInt(idUsuario))
		return;

	for(auto usuario : this->vectorUsuarios) {
		if(usuario.getId() == idUsuario) {
			if(!this->confirmarAcao("Tem certeza que deseja remover este Usuario?\n"))
				return;
			this->vectorUsuarios.erase(this->vectorUsuarios.begin() + posicaoUsuario);
			this->arquivoUsuarios->atualizarDados(this->vectorUsuarios);
			cout << "Usuario removido com sucesso" << endl;
			return;
		}
		posicaoUsuario++;
	}
	cout << "Nao ha Usuario cadastrado com esse CPF" << endl;
}

/*
Listar Emprestimos - exibe uma lista com todos os emprestimos e seus dados
*/
void Biblioteca::listarEmprestimos() {
	cout << "\nEmprestimos:" << endl;
	for(auto emprestimo : this->vectorEmprestimos)
		cout << emprestimo.toString() << endl;
}

/*
Pesquisar Emprestimo - pesquisa e exibe, se encontrado, um emprestimo
com ID informado pelo bibliotecario
*/
void Biblioteca::pesquisarEmprestimo() {
	int id;
	cout << "\nDigite o ID do Emprestimo desejado (ou digite ':C' para cancelar):" << endl;
	if(!this->getEntradaInt(id))
		return;
	for(auto emprestimo : this->vectorEmprestimos) {
		if(emprestimo.getIdEmprestimo() == id) {
			cout << emprestimo.toString() << endl;
			return;
		}
	}
	cout << "Nao ha nenhum emprestimo cadastrado com esse ID" << endl;
}

/*
Realizar Emprestimo - realiza um emprestimo de um livro com ID especifico
para um usuario com ID especifico
*/
void Biblioteca::realizarEmprestimo() {
	int idUsuario, idLivro, numCopias, multa = 0;
	
	cout << "\nDigite o ID do Usuario (ou digite ':C' para cancelar):";
	if(!this->getEntradaInt(idUsuario))
		return;
		
	cout << "Digite o ID do Livro (ou digite ':C' para cancelar):";
	if(!this->getEntradaInt(idLivro))
		return;

	if(!this->verificarCondicoesEmprestimo(idLivro, idUsuario))
		return;

	if(!this->confirmarAcao("Confirmar realizacao do emprestimo?\n"))
		return;

	int diaRealizacao, mesRealizacao, anoRealizacao;

	diaRealizacao = data.getDia();
	mesRealizacao = data.getMesValor();
	anoRealizacao = data.getAno();

	Emprestimo aluguel(getIdNovoEmprestimo(), idLivro, idUsuario, diaRealizacao, mesRealizacao, anoRealizacao, multa);
	this->vectorEmprestimos.push_back(aluguel);

	this->arquivoLivros->atualizarDados(this->vectorLivros);
	this->arquivoEmprestimos->atualizarDados(this->vectorEmprestimos);
	this->arquivoUsuarios->atualizarDados(this->vectorUsuarios);
	cout << "Emprestimo realizado" << endl;
}

/*
Verificar condicoes para emprestimo - verifica se o usuario pode alugar o livro e
se o livro pode ser alugado. Se sim, reduz a quantidade de livros disponiveis
e altera o status do usuario para nao alugar outros livros

@see realizarEmprestimo

@param idLivro int que representa o ID do livro a ser alugado
@param idUsuario int que representa o ID do usuario que deseja alugar um livro

@return true, se o emprestimo pode ser feito
@return false, se ha inconsistencia e o emprestimo nao pode ser feito
*/
bool Biblioteca::verificarCondicoesEmprestimo(int idLivro, int idUsuario) {
	Livro* l;
	Usuario* u;
	u = this->existeUsuario(idUsuario);
	if(u == nullptr) {
		cout << "Nao ha usuario com esse ID" << endl;
		return false;
	}
	if(!u->getStatus()) {
		cout << "Usuario nao pode alugar livros pois esta em situacao pendente" << endl;
		return false;
	}
	l = this->existeLivro(idLivro);
	if(l == nullptr) {
		cout << "Nao ha livro com esse ID" << endl;
		return false;
	}
	if(l->getQuantidadeDeCopias() <= 0) {
		cout << "Nao ha nenhum exemplar disponivel do livro desejado" << endl;
		return false;
	}
	l->setQuantidadeDeCopias(l->getQuantidadeDeCopias() - 1);
	u->setStatus(0);
	return true;
}

/*
Realizar Devolucao - verifica se os dados de uma devolucao com ID especifico
constam no sistema e, se estiver tudo certo, realiza uma devolucao, aumentando
a quantidade de livros disponiveis e liberando o usuario para alugar outro livro 
*/
void Biblioteca::realizarDevolucao() {
	int idEmprestimo, idLivro = 0, idUsuario = 0, numCopias, posicaoEmprestimo = 0;
	Livro* l;
	Usuario* u;
	string dataPrevista;
	cout << "\nDigite o ID do Emprestimo a ser devolvido (ou digite ':C' para cancelar):" << endl;
	if(!this->getEntradaInt(idEmprestimo))
		return;
	for(auto emprestimo : this->vectorEmprestimos) {
		if(emprestimo.getIdEmprestimo() == idEmprestimo) {
			this->vectorEmprestimos.erase(this->vectorEmprestimos.begin() + posicaoEmprestimo);
			idLivro = emprestimo.getIdLivro();
			idUsuario = emprestimo.getIdUsuario();
			break;
		}
		posicaoEmprestimo++;
	}
	if(idLivro == 0) {
		cout << "Nao ha emprestimo com esse ID" << endl;
		return;
	}
	l = this->existeLivro(idLivro);
	if(l == nullptr) {
		cout << "\nLivro nao encontrado nos registros" << endl;
		return;
	}
	l->setQuantidadeDeCopias(l->getQuantidadeDeCopias() + 1);
	u = this->existeUsuario(idUsuario);
	if(u == nullptr) {
		cout << "\nUsuario nao encontrado nos registros" << endl;
		return;
	}
	u->setStatus(1);
	cout << "\nDevolucao realizada com sucesso." << endl;
	this->arquivoLivros->atualizarDados(this->vectorLivros);
	this->arquivoEmprestimos->atualizarDados(this->vectorEmprestimos);
	this->arquivoUsuarios->atualizarDados(this->vectorUsuarios);
}

/*
Listar Reservas - exibe uma lista com todas as reservas e seus dados
*/
void Biblioteca::listarReservas() {
	cout << "\nReservas:" << endl;
	for(auto reserva : this->vectorReservas)
		cout << reserva.toString() << endl;
}

/*
Pesquisar Reserva - pesquisa e exibe, se encontrada, uma reserva
com ID informado pelo bibliotecario
*/
void Biblioteca::pesquisarReserva() {
	int idReserva, numReservas = 0;
	cout << "\nDigite o ID da reserva (ou digite ':C' para cancelar):" << endl;
	if(!this->getEntradaInt(idReserva))
		return;
	for(auto reserva : this->vectorReservas) {
		if(reserva.getIdReserva() == idReserva) {
			cout << reserva.toString() << endl;
			return;
		}
	}
	cout << "Nao ha nenhuma reserva cadastrada com esse ID" << endl;
}

/*
Realizar Reserva - realiza uma reserva de um livro com ID especifico
para um usuario com ID especifico
*/
void Biblioteca::realizarReserva() {
	int idLivro, idUsuario;
	string dataPrevista;
	
	cout << "\nDigite o ID do Livro a ser reservado (ou digite ':C' para cancelar):" << endl;
	if(!this->getEntradaInt(idLivro))
		return;
		
	cout << "Digite o ID do Usuario que deseja a reserva:" << endl;
	if(!this->getEntradaInt(idUsuario))
		return;
		
	if(!this->verificarCondicoesReserva(idLivro, idUsuario))
		return;

	Reserva novaReserva(this->getIdNovaReserva(), idUsuario, idLivro);

	this->vectorReservas.push_back(novaReserva);
	this->arquivoReservas->atualizarDados(this->vectorReservas);

	cout << "Reserva realizada com sucesso" << endl;
}

/*
Verificar condicoes de reserva - valida o livro e o usuario informados, 
verificando se e' possivel realizar a reserva

@param idLivro int que representa o ID do livro a ser alugado
@param idUsuario int que representa o ID do usuario que deseja alugar um livro

@return true, se for possivel realizar a reserva sem restricoes
@return false, se nao for possivel realizar a reserva
*/
bool Biblioteca::verificarCondicoesReserva(int idLivro, int idUsuario) {
	Livro* l = this->existeLivro(idLivro);
	Usuario* u = this->existeUsuario(idUsuario);
	if(l == nullptr) {
		cout << "Nao existe livro com esse ID" << endl;
		return false;
	}
	if(u == nullptr) {
		cout << "Nao existe usuario com esse ID" << endl;
		return false;
	}
	if(l->getQuantidadeDeCopias() > 0) {
		cout << "O livro desejado ja tem exemplares disponiveis" << endl;
		return false;
	}
	if(u->getStatus() == 0) {
		cout << "O usuario esta em situacao pendente" << endl;
		return false;
	}
	for(auto reserva : this->vectorReservas) {
		if(reserva.getIdUsuario() == idUsuario) {
			cout << "O Usuario ja reservou um livro" << endl;
			return false;
		} else if(reserva.getIdLivro() == idLivro) {
			cout << "O Livro ja tem uma reserva pendente" << endl;
			return false;
		}
	}
	return true;
}

/*
Cancelar Reserva - cancela uma reserva com um ID especifico
*/
void Biblioteca::cancelarReserva() {
	int idReserva, posicaoReserva = 0;
	cout << "\nDigite o ID da reserva que deseja cancelar (ou digite ':C' para cancelar):" << endl;
	if(!this->getEntradaInt(idReserva))
		return;
	for(auto reserva : this->vectorReservas) {
		if(reserva.getIdReserva() == idReserva) {
			this->vectorReservas.erase(this->vectorReservas.begin() + posicaoReserva);
			this->arquivoReservas->atualizarDados(this->vectorReservas);
			cout << "Reserva cancelada com sucesso" << endl;
			return;
		}
		posicaoReserva++;
	}
	cout << "Nao ha reserva com esse ID" << endl;
}

/*
Renovar Emprestimo - renova um emprestimo com ID especifico
*/
void Biblioteca::renovarEmprestimo() {
	bool encontrado = false;
	int idEmprestimo, prazoRenovacao = 7;
	Data dataAux;
	
	cout << "\nInforme o ID do Emprestimo (ou digite ':C' para cancelar):" << endl;
	if(!this->getEntradaInt(idEmprestimo))
		return;

	for(auto &emprestimo : this->vectorEmprestimos) {
		if(emprestimo.getIdEmprestimo() == idEmprestimo) {
			if(this->existeUsuario(emprestimo.getIdUsuario()) == nullptr) {
				cout << "\nUsuario nao encontrado no sistema" << endl;
				return;
			}
			if(this->existeLivro(emprestimo.getIdLivro()) == nullptr) {
				cout << "\nLivro nao encontrado no sistema" << endl;
				return;
			}
			for(auto reserva : this->vectorReservas) {
				if(reserva.getIdLivro() == emprestimo.getIdLivro()) {
					cout << "\nExiste uma reserva pendente para esse livro" << endl;
					return;
				}
			}
			if(data.getMesValor() != emprestimo.getMesDevolucao() || data.getDia() != emprestimo.getDiaDevolucao()) {
				cout << "\nSo e possivel renovar no dia da devolucao" << endl;
				return;
			}
			emprestimo.setDiaRealizacao(data.getDia());
			emprestimo.setMesRealizacao(data.getMesValor());
			emprestimo.setAnoRealizacao(data.getAno());
			for(int i = 0 ; i < prazoRenovacao ; i++)
				dataAux++;

			emprestimo.setDiaDevolucao(dataAux.getDia());
			emprestimo.setMesDevolucao(dataAux.getMesValor());
			emprestimo.setAnoDevolucao(dataAux.getAno());

			this->arquivoEmprestimos->atualizarDados(this->vectorEmprestimos);
			cout << "\nEmprestimo renovado" << endl;
			return;
		}
	}
	cout << "\nNao existe nenhum emprestimo com esse ID" << endl;
}

/*
Get ID Novo Livro - le o arquivo de livros e retorna um novo ID nao utilizado

@return idLivro int que representa um novo ID para ser adicionado
*/
int Biblioteca::getIdNovoLivro() {
	int maximo = -1;
	for(auto livro : this->vectorLivros) {
		if(maximo < livro.getId()) {
			maximo = livro.getId();
		}
	}
	return maximo + 1;
}

/*
Get ID Novo Usuario - le o arquivo de usuarios e retorna um novo ID nao utilizado

@return idUsuario int que representa um novo ID para ser adicionado
*/
int Biblioteca::getIdNovoUsuario() {
	int maximo = -1;
	for(auto usuario : this->vectorUsuarios) {
		if(maximo < usuario.getId()) {
			maximo = usuario.getId();
		}
	}
	return maximo + 1;
}

/*
Get ID Novo Emprestimo - le o arquivo de emprestimos e retorna um novo ID nao utilizado

@return idEmprestimo int que representa um novo ID para ser adicionado
*/
int Biblioteca::getIdNovoEmprestimo() {
	int maximo = -1;
	for(auto emprestimo : this->vectorEmprestimos) {
		if(maximo < emprestimo.getIdEmprestimo()) {
			maximo = emprestimo.getIdEmprestimo();
		}
	}
	return maximo + 1;
}

/*
Get ID Nova Reserva - le o arquivo de reservas e retorna um novo ID nao utilizado

@return idReserva int que representa um novo ID para ser adicionado
*/
int Biblioteca::getIdNovaReserva() {
	int maximo = -1;
	for(auto reservas : this->vectorReservas) {
		if(maximo < reservas.getIdReserva()) {
			maximo = reservas.getIdReserva();
		}
	}
	return maximo + 1;
}

/*
Exibir confirmacao de login - exibe uma mensagem confirmando que o login foi
realizado com sucesso
*/
void Biblioteca::exibirConfirmacaoLogin() {
	system("CLS");
	char genero = this->bibliotecarioAtual->getSexo() == 'F' ? 'a' : 'o';
	cout << "\nSeja bem vind" << genero << " a \"" << this->nome << "\"!" << endl;
}

/*
Mostrar Data - exibe a data atual
*/
void Biblioteca::mostrarData() {
	cout << data << endl;
}

/*
Exibir menu - exibe as opcoes disponiveis para navegar entre as telas
e trata o valor informado pelo bibliotecario
*/
void Biblioteca::exibirMenu() {
	string opcao = "";
	this->mostrarData();

	while (true) {
		this->telaAtual->mostrar();
		cin >> opcao;
		cin.ignore();
		if(opcao == "S" || opcao == "s" || opcao == "SAIR") {
			break;
		} else if(opcao == "V" || opcao == "v" || opcao == "VOLTAR") {
			delete this->telaAtual;
			this->telaAtual = new TelaPrincipal();
		} else {
			this->verificarOpcaoPorTela(opcao);
		}
	}
}

/*
Verificar opcao por tela - navega entre as telas de acordo com a opcao informada
*/
void Biblioteca::verificarOpcaoPorTela(string opcao) {
	system("CLS");
	if(this->telaAtual->getNomeTela() == "TelaPrincipal") {
		this->verificarOpcaoTelaPrincipal(opcao);
	} else if(this->telaAtual->getNomeTela() == "TelaLivros") {
		this->verificarOpcaoTelaLivros(opcao);
	} else if(this->telaAtual->getNomeTela() == "TelaUsuarios") {
		this->verificarOpcaoTelaUsuarios(opcao);
	} else if(this->telaAtual->getNomeTela() == "TelaTransacoes") {
		this->verificarOpcaoTelaTransacoes(opcao);
	}
}

/*
Verificar opcao tela principal - escolhe o proximo passo baseado nas
opcoes da tela principal
*/
void Biblioteca::verificarOpcaoTelaPrincipal(string opcao) {
	system("CLS");
	if(opcao == "1") {
		delete this->telaAtual;
		this->telaAtual = new TelaLivros();
	} else if(opcao == "2") {
		delete this->telaAtual;
		this->telaAtual = new TelaUsuarios();
	} else if(opcao == "3") {
		delete this->telaAtual;
		this->telaAtual = new TelaTransacoes();
	}
}

/*
Verificar opcao tela de livros - escolhe o proximo passo baseado nas
opcoes da tela de livros
*/
void Biblioteca::verificarOpcaoTelaLivros(string opcao) {
	system("CLS");
	if(opcao == "1") {
		this->listarLivros();
	} else if(opcao == "2") {
		this->pesquisarLivro();
	} else if(opcao == "3") {
		this->atualizarLivro();
	} else if(opcao == "4") {
		this->adicionarLivro();
	} else if(opcao == "5") {
		this->removerLivro();
	}
	system("PAUSE");
	system("CLS");
}

/*
Verificar opcao tela de usuarios - escolhe o proximo passo baseado nas
opcoes da tela de usuarios
*/
void Biblioteca::verificarOpcaoTelaUsuarios(string opcao) {
	system("CLS");
	if(opcao == "1") {
		this->listarUsuarios();
	} else if(opcao == "2") {
		this->pesquisarUsuario();
	} else if(opcao == "3") {
		this->atualizarUsuario();
	} else if(opcao == "4") {
		this->adicionarUsuario();
	} else if(opcao == "5") {
		this->removerUsuario();
	}
	system("PAUSE");
	system("CLS");
}

/*
Verificar opcao tela de transacoes - escolhe o proximo passo baseado nas
opcoes da tela de transacoes
*/
void Biblioteca::verificarOpcaoTelaTransacoes(string opcao) {
	system("CLS");
	if(opcao == "1") {
		this->listarEmprestimos();
	} else if(opcao == "2") {
		this->pesquisarEmprestimo();
	} else if(opcao == "3") {
		this->listarReservas();
	} else if(opcao == "4") {
		this->pesquisarReserva();
	} else if(opcao == "5") {
		this->realizarEmprestimo();
	} else if(opcao == "6") {
		this->realizarDevolucao();
	} else if(opcao == "7") {
		this->realizarReserva();
	} else if(opcao == "8") {
		this->cancelarReserva();
	} else if(opcao == "9") {
		this->renovarEmprestimo();
	}
	system("PAUSE");
	system("CLS");
}

/*
Get entrada valida - recebe uma entrada e trata para evitar a propagacao de
erros

@param entrada string passada por referencia para atribuir o valor da entrada
@param bloquearEntradaVazia bool para definir se devem ser bloqueadas (caso seja true)
ou nao (caso seja false) entradas vazias

@return true, entrada valida
@return false, entrada invalida
*/
bool Biblioteca::getEntradaValida(string& entrada, bool bloquearEntradaVazia) {
	entrada = "";
	while(true) {
		getline(cin, entrada);
		this->removerEspacos(entrada);
		if(entrada == ":C")
			break;
		if(bloquearEntradaVazia && entrada.empty()) {
			cout << "Por favor, informe um valor valido ou digite ':C' para cancelar." << endl;
			continue;
		}
		size_t posicaoInvalida = entrada.find(";");
		if(posicaoInvalida == string::npos) {
			return true;
		}
		cout << "O caractere ';' e' invalido. Por favor, informe um valor valido ou digite ':C' para cancelar." << endl;
	}
	return false;
}

/*
Get entrada int - recebe uma entrada verificando se e' um valor 

@param entrada string passada por referencia para atribuir o valor da entrada

@return true, entrada valida
@return false, entrada invalida
*/
bool Biblioteca::getEntradaInt(int& entrada) {
	string s = "";
	while(true) {
		getline(cin, s);
		if(s == ":C")
			break;
		stringstream ss(s);
		if(ss >> entrada && entrada >= 0)
			return true;
		cout << "Numero invalido. Informe um numero valido ou digite ':C' para cancelar" << endl;
	}
	return false;
}

/*
Confirmar acao - exibe uma mensagem e analisa a entrada do usuario

@param fraseConfirmacao string com uma frase de confirmacao para ser exibida

@return true, se o bibliotecario confirmou
@return false, se o bibliotecario recusou
*/
bool Biblioteca::confirmarAcao(string fraseConfirmacao) {
	string opcao;
	cout << fraseConfirmacao << "Digite 'S' para sim ou 'N' para nao" << endl;
	cin >> opcao;
	while((opcao != "S") && (opcao != "N")) {
		cout << "Digite uma opcao valida:\n" << " 'S' para sim ou 'N' para nao" << endl;
		cin >> opcao;
	}
	cin.ignore();
	return opcao == "S";
}

/*
Remover espacos - remove espacos de uma string para validacao

@param linha string passada por referencia para remover os espacos
*/
void Biblioteca::removerEspacos(string& linha) {
	string espacos = "\t\n\v\f\r ";
	linha.erase(0, linha.find_first_not_of(espacos));
	linha.erase(linha.find_last_not_of(espacos) + 1);
}