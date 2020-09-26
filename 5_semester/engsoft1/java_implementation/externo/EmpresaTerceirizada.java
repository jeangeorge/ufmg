package externo;

public class EmpresaTerceirizada {
  private int id;
  private String nome;
  private String descricao;
  private String cnpj;

  public EmpresaTerceirizada(String nome, String descricao, String cnpj) {
    this.nome = nome;
    this.descricao = descricao;
    this.cnpj = cnpj;
  }

  public EmpresaTerceirizada(int id, String nome, String descricao, String cnpj) {
    this.id = id;
    this.nome = nome;
    this.descricao = descricao;
    this.cnpj = cnpj;
  }
}
