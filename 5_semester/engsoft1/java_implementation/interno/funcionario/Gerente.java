package interno.funcionario;

public class Gerente extends Funcionario {
  public Gerente(String nome, float salario) {
    super(nome, salario);
  }

  public Gerente(int id, String nome, float salario) {
    super(id, nome, salario);
  }

  public boolean contratarMaoDeObra() {
    return true;
  }
}
