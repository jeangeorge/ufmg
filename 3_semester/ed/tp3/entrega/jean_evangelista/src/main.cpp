#include "Tree.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

int main(int argc, char *argv[]) {
    bool show = false; // Variável para saber se será necessário mostrar a árvore ou não
    Tree* tree = new Tree(); // Minha arvore
    std::string code, message = "", line; // strings que serão utilizadas na leitura
    std::stringstream lineStream; // stream utilizado na leitura

    // Constroi a arvore
    if (!tree->buildTree("./morse.txt")) {
        // caso não construir a árvore termina o programa
        delete tree;
        return 0;
    }

    // Avalia se é necessário mostrar a árvore de acordo com o argumento
    if (argv[1]) {
        std::string arg1 = argv[1];
        if (!arg1.compare("-a")) {
            show = true;
        }
    }

    // Lê a entrada padrão linha a linha
    while(std::getline(std::cin, line)) {
        lineStream << line; // Armazena a linha em lineStream
        // Separa a linha por espaços, armazendo cada resultado na variável code
        while(std::getline(lineStream,code,' ')) {
            // / equivale a um espaço
            if (code != "/") {
                message += tree->decode(code);
            } else {
                message += " ";
            }
        }
        message += "\n";
        lineStream.clear(); // reseta a stream
    }

    std::cout << message; // printa a mensagem

    // Caso seja necessário, mostra a árvore em caminhamento pré-ordem
    if (show) {
        std::cout << std::endl;
        tree->printPreOrder();
    }

    delete tree;

    return 0;
}