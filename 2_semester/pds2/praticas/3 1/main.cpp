#include <vector>
#include <string>
#include <iostream>
#include "Professor.hpp"
#include "Estudante.hpp"

using std::cout;
using std::endl;

int main()
{
  vector<Pessoa*> pessoas;

  Estudante estudante1("Joao", "Avenida das Embaúbas");
  Estudante estudante2("Maria", "Rua Dezessete");
  Estudante estudante3("Isadora", "Rua Carlos Bello Wagner");

  Professor professor1("Abelardo", "Rua Capivari");
  Professor professor2("Jonas", "Travessa Construtor Severino Bezerra");

  estudante1.adicionarCursoNota("DCC190",91);
  estudante1.adicionarCursoNota("DCC192",86);
  estudante1.adicionarCursoNota("DCC193",87);
  estudante1.adicionarCursoNota("DCC800",98);
  estudante1.adicionarCursoNota("DCC801",100);
  cout << estudante1.getNotaMedia() << endl;

  estudante2.adicionarCursoNota("DCC190",84);
  estudante2.adicionarCursoNota("DCC192",74);
  estudante2.adicionarCursoNota("DCC193",81);
  estudante2.adicionarCursoNota("DCC800",72);
  estudante2.adicionarCursoNota("DCC801",100);
  cout << estudante2.getNotaMedia() << endl;

  estudante3.adicionarCursoNota("DCC190",56);
  estudante3.adicionarCursoNota("DCC193",60);
  estudante3.adicionarCursoNota("DCC800",45);
  estudante3.adicionarCursoNota("DCC801",66);
  cout << estudante3.getNotaMedia() << endl;

  professor1.adicionarCurso("DCC190");
  professor1.adicionarCurso("DCC192");
  professor1.adicionarCurso("DCC193");
  professor1.adicionarCurso("DCC800");
  professor1.adicionarCurso("DCC801");

  professor2.adicionarCurso("DCC190");
  professor2.adicionarCurso("DCC801");

  cout << "Estudante 2 matriculado nos cursos" << endl;
  for(auto curso : estudante2.getCursos()){
    cout << curso << endl;
  }

  cout << "Professor 1 esta nos cursos" << endl;
  for(auto curso : professor1.getCursos()){
    cout << curso << endl;
  }
  if(professor1.removerCurso("DCC190")){
    cout << "Removido com sucesso" << endl;
    for(auto curso : professor1.getCursos()){
      cout << curso << endl;
    }
  }

  if(!professor1.removerCurso("DCC194"))
  {
    cout << "Nao encontrado" << endl;
  }

  if(!professor2.adicionarCurso("DCC801")){
    cout << "Curso ja existe" << endl;
  }

  pessoas.push_back(&estudante1);
  pessoas.push_back(&estudante2);
  pessoas.push_back(&estudante3);
  pessoas.push_back(&professor1);
  pessoas.push_back(&professor2);

  for(auto pessoa : pessoas){
    pessoa->imprimeInformacoes();
  }

}
