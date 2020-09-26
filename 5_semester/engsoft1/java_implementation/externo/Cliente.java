package externo;

public class Cliente {
  private int id;
  private String nome;
  private String endereco;

  public Cliente(String nome, String endereco) {
    this.nome = nome;
    this.endereco = endereco;
  }

  public Cliente(int id, String nome, String endereco) {
    this.id = id;
    this.nome = nome;
    this.endereco = endereco;
  }
}
