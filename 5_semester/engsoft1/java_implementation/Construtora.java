import java.util.ArrayList;
import java.util.List;
import java.util.Random;

import externo.*;
import interno.funcionario.*;
import interno.projeto.*;

public class Construtora {
    private String nome = "Construtora do Jean";

    private List<Cliente> clientes;
    private List<EmpresaTerceirizada> empresasTerceirizadas;
    private List<Fornecedor> fornecedores;
    private List<OrgaoPublico> orgaoPublicos;
    private List<Atendente> atendentes;
    private List<Engenheiro> engenheiros;
    private Gerente gerente;
    private List<TecnicoJuridico> tecnicos;

    public Construtora() {
        this.clientes = new ArrayList<>();
        this.empresasTerceirizadas = new ArrayList<>();
        this.fornecedores = new ArrayList<>();
        this.orgaoPublicos = new ArrayList<>();
        this.atendentes = new ArrayList<>();
        this.engenheiros = new ArrayList<>();
        this.gerente = new Gerente("Gerente", 15000);
        carregarDados();
    }

    private void carregarDados() {
        for (int i = 0; i < gerarNumeroInteiroAleatorio(1, 100); i++) {clientes.add(new Cliente(i, "Cliente " + i, "Endereço" + i));
        }
        for (int i = 0; i < gerarNumeroInteiroAleatorio(1, 20); i++) {
            empresasTerceirizadas.add(new EmpresaTerceirizada(i, "Empresa Terceirizada " + i, "Descrição " + i, "CNPJ " + i));
        }
        for (int i = 0; i < gerarNumeroInteiroAleatorio(1, 10); i++) {
            fornecedores.add(new Fornecedor(i, "Telefone " + i, "Nome Fantasia " + i, "Email " + i, "Documento " + i));
        }
        for (int i = 0; i < gerarNumeroInteiroAleatorio(1, 10); i++) {
            orgaoPublicos.add(new OrgaoPublico(i, "Orgao " + i));
        }
        for (int i = 0; i < gerarNumeroInteiroAleatorio(1, 10); i++) {
            atendentes.add(new Atendente(i, "Atendente " + i, 1059, gerarNumeroInteiroAleatorio(1000, 9000)));
        }
        for (int i = 0; i < gerarNumeroInteiroAleatorio(1, 3); i++) {
            engenheiros.add(new Engenheiro(i, "Engenheiro " + i, 9000, String.format("%012d", gerarNumeroInteiroAleatorio(1, 999999999))));
        }
        for (int i = 0; i < gerarNumeroInteiroAleatorio(1, 5); i++) {
            tecnicos.add(new TecnicoJuridico(i, "Tecnico Juridico " + i, 5000));
        }
    }

    private int gerarNumeroInteiroAleatorio(int min, int max) {
        if (min >= max) {
            throw new IllegalArgumentException("max must be greater than min");
        }

        Random random = new Random();
        return random.nextInt((max - min) + 1) + min;
    }

    public static void main(String[] args) {
        new Construtora();
    }
}
