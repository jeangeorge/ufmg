package interno.funcionario;

import java.util.ArrayList;
import java.util.List;

import interno.projeto.Projeto;

public class Engenheiro extends Funcionario {
  private String crea;
  private List<Projeto> projetosGerenciados;

  public Engenheiro(String nome, float salario, String crea, List<Projeto> projetosGerenciados) {
    super(nome, salario);
    this.crea = crea;
    this.projetosGerenciados = projetosGerenciados;
  }

  public Engenheiro(int id, String nome, float salario, String crea, List<Projeto> projetosGerenciados) {
    super(id, nome, salario);
    this.crea = crea;
    this.projetosGerenciados = projetosGerenciados;
  }

  public Engenheiro(int id, String nome, float salario, String crea) {
    super(id, nome, salario);
    this.crea = crea;
    this.projetosGerenciados = new ArrayList<>();
  }

  public boolean contratarServicos() {
    return true;
  }
}
