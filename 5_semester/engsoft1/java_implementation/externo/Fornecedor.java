package externo;

public class Fornecedor {
  private int id;
  private String telefone;
  private String nomeFantasia;
  private String email;
  private String documento;

  public Fornecedor(String telefone, String nomeFantasia, String email, String documento) {
    this.telefone = telefone;
    this.nomeFantasia = nomeFantasia;
    this.email = email;
    this.documento = documento;
  }

  public Fornecedor(int id, String telefone, String nomeFantasia, String email, String documento) {
    this.id = id;
    this.telefone = telefone;
    this.nomeFantasia = nomeFantasia;
    this.email = email;
    this.documento = documento;
  }

  public boolean fornecerMateriais() {
    return true;
  }
}
