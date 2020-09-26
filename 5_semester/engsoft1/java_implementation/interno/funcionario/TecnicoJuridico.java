package interno.funcionario;

public class TecnicoJuridico extends Funcionario {
  public TecnicoJuridico(String nome, float salario) {
    super(nome, salario);
  }

  public TecnicoJuridico(int id, String nome, float salario) {
    super(id, nome, salario);
  }

  public boolean contatarOrgaoPublico() {
    return true;
  }
}
