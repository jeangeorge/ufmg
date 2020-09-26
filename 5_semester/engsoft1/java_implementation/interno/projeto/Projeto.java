package interno.projeto;

public class Projeto {
  private int id;
  private ProjetoEnum tipo;
  private String descricao;

  public Projeto() {

  }

  public Projeto(ProjetoEnum tipo, String descricao) {
    this.tipo = tipo;
    this.descricao = descricao;
  }

  public Projeto(int id, ProjetoEnum tipo, String descricao) {
    this.id = id;
    this.tipo = tipo;
    this.descricao = descricao;
  }
}
