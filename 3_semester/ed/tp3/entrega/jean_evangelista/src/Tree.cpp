#include "Tree.hpp"
#include "Code.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

Tree::Tree() {
    // Inicializa o no raiz
    this->root = new Node();
}

Tree::~Tree() {
    delete this->root;
}

// Constroi a arvore a partir do arquivo
bool Tree::buildTree(std::string filename) {
    std::ifstream file; // Arquivo de leitura
    std::string line; // Cada linha do arquivo

    // Abre o arquivo
    file.open(filename);

    // Verifica se o arquivo foi aberto
    if (file.is_open()) {
        // Pega linha a linha do arquivo
        while (std::getline(file,line)) {
            std::stringstream lineStream(line); // Stream auxiliar para separar a linha por espaços
            std::string value; // Variavel em que é salva cada um dos dois valores da linha
            int count = 0;  // Variavel auxiliar
            Code code; // Objeto para salvar o codigo e a letra

            // Pega os valores de cada linha utilizando espaço como delimitador
            while(std::getline(lineStream,value,' ')) {
                if (count == 0) {
                    code.letter = value.at(0); // Primeiro valor da linha: letra
                } else {
                    code.symbol = value; // Segundo valor da linha: simbolo
                }
                count++;
            }

            // Adiciona o codigo na arvore
            this->add(code);
        }

        file.close(); // Fecha o arquivo

        // Verifica se o arquivo foi fechado
        if (!file.is_open()) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

// Função para adicionar na arvore, recebe o codigo a ser adicionado
void Tree::add(Code code) {
    Node* aux = this->root; // No auxiliar

    // Percorre a string simbolo morse caracter a caracter
    for (unsigned int i=0; i<code.symbol.length(); i++) {
        // . vai pra esquerda e - vai pra direita
        if (code.symbol.at(i) == '.') {
            if (aux->left == nullptr) {
                aux->left = new Node();
            }
            aux = aux->left;
        } else {
            if (aux->right == nullptr) {
                aux->right = new Node();
            }
            aux = aux->right;
        }
    }
    // Armazena o caracter e o simbolo no nó
    aux->code->symbol = code.symbol;
    aux->code->letter = code.letter;
}

// Função de decodificação, recebe o código a ser decodificado
char Tree::decode(std::string code) {
    Node* aux = this->root; // No auxiliar
    for (unsigned int i=0; i<code.length(); i++) {
        // . vai pra esquerda e - vai pra direita
        if (code.at(i) == '.') {
            aux = aux->left;
        } else {
            aux = aux->right;
        }
    }
    // retorna a letra
    return aux->code->letter;
}

// Funções para printar em pré-ordem
void Tree::printPreOrder(Node* node) {
    if (node != nullptr) {
        if (node->code->letter != ' ') {
            std::cout << node->code->letter << " " << node->code->symbol << std::endl;
        }
    }
    if (node->left != nullptr) {
        printPreOrder(node->left);
    }
    if (node->right != nullptr) {
        printPreOrder(node->right);
    }
}
void Tree::printPreOrder() {
    Node* node = this->root;
    if (node != nullptr) {
        if (node->code->letter != ' ') {
            std::cout << node->code->letter << " " << node->code->symbol << std::endl;
        }
    }
    if (node->left != nullptr) {
        printPreOrder(node->left);
    }
    if (node->right != nullptr) {
        printPreOrder(node->right);
    }
}