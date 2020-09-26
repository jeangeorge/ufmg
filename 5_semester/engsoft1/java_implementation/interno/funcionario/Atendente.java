package interno.funcionario;

public class Atendente extends Funcionario {
  private int ramal;

  public Atendente(String nome, float salario, int ramal) {
    super(nome, salario);
    this.ramal = ramal;
  }

  public Atendente(int id, String nome, float salario, int ramal) {
    super(id, nome, salario);
    this.ramal = ramal;
  }

  public boolean atenderCliente() {
    return true;
  }
}
