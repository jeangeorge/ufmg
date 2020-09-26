package interno.funcionario;

public class Funcionario {
  protected int id;
  protected String nome;
  protected float salario;

  public Funcionario(String nome, float salario) {
    this.nome = nome;
    this.salario = salario;
  }

  public Funcionario(int id, String nome, float salario) {
    this.id = id;
    this.nome = nome;
    this.salario = salario;
  }
}
