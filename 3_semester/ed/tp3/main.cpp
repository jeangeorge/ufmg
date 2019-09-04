#include "Tree.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

int main(int argc, char *argv[]) {
    bool show = false; // Variável para saber se será necessário mostrar a árvore ou não
    Tree* tree = new Tree(); // Minha arvore // LEMBRAR DE MUDAR NA VERSAO FINAL
    std::string code, message = "", line;
    std::stringstream lineStream;

    // Constroi a arvore
    tree->buildTree("./morse.txt");

    // Avalia se é necessário mostrar a árvore de acordo com o argumento
    if (argv[1]) {
        std::string arg1 = argv[1];
        if (!arg1.compare("-a")) {
            show = true;
        }
    }

    while(std::getline(std::cin, line)) {
        lineStream << line;
        while(std::getline(lineStream,code,' ')) {
            if (code != "/") {
                message += tree->decode(code);
            } else {
                message += " ";
            }
        }
        message += "\n";
        lineStream.clear();
    }

    std::cout << message;

    if (show) {
        std::cout << std::endl;
        tree->printPreOrder();
    }

    delete tree;

    return 0;
}