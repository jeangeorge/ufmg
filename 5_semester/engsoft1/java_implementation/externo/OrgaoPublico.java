package externo;

public class OrgaoPublico {
  private int id;
  private String nome;

  public OrgaoPublico(int id, String nome) {
    this.id = id;
    this.nome = nome;
  }

  public OrgaoPublico(String nome) {
    this.nome = nome;
  }
}
