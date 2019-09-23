#include <iostream>
#include <fstream>

#include "Node.hpp"
#include "Edge.hpp"
#include "Graph.hpp"

using std::cout;
using std::endl;
using std::vector;
using std::ifstream;

// V: número de vértices, A: número de arestas
int main(int argc, char** argv) {
    ifstream file (argv[1]);

    // Se arquivo não foi aberto, já encerra o programa
    if (!file.is_open()) {
        return 0;
    }

    int members, relationships, instructions; // quantidades: nós, vertices e comandos

    file >> members >> relationships >> instructions; // leitura das quantidades

    vector<Node> nodes; // vector de nós para todos os membros
    vector<Edge> edges; // vector de arestas / relações

    // Redimensiona os vectors de acordo com as quantidades
    // Complexidade: O(V + A)
    nodes.resize(members);
    edges.resize(relationships);

    // Preenche os nós com os dados membros do grafo (id e idade)
    // Complexidade: O(V)
    for (int i=0; i<members; i++) {
        int age; // variavel para armazenar a idade de cada membro
        file >> age;
        nodes[i] = Node(i,age);
    }

    // Preenche as arestas com as relações de comando
    // Complexidade: O(A)
    for (int i=0; i<relationships; i++) {
        int source, destiny;
        file >> source >> destiny;
        edges[i] = Edge(nodes[source-1],nodes[destiny-1]); // -1 porque os ids dos membros iniciam-se no 1 e o vector começa no indice 0
    }

    // Instancia o grafo, passando as arestas, o numero de nós e o numero de arestas
    // Complexidade de construção do grafo: O(V + A)
    Graph *graph = new Graph(nodes,edges,members,relationships);

    // Inicia a leitura das instruções
    // Complexidade: Entendi que nesse laço é irrelevante, a complexidade de cada função é analisada dentro da mesma
    for (int i=0; i<instructions; i++) {
        char instruction;
        file >> instruction;
        // swap
        if (instruction == 'S') {
            // Faz a leitura dos membros que se quer trocar
            int a,b;
            file >> a >> b;
            // cout << "Antes:" << endl;
            // graph->print();
            if (graph->swap(a-1,b-1)) {
                cout << "S T" << endl;
            } else {
                cout << "S N" << endl;
            }
            // cout << "Depois:" << endl;
            // graph->print();
        }
        // command
        else if (instruction == 'C') {
            // Le o membro e mostra o comandante mais novo
            int a, age;
            file >> a;
            age = graph->commander(a-1);
            cout << "C ";
            if (age == -1) {
                cout << "*" << endl;
            } else {
                cout << age << endl;
            }
        }
        // meeting
        else if (instruction == 'M') {
            cout << "M ";
            graph->meeting();
            cout << endl;
        }
    }

    delete graph;
    file.close();
    return 0;
}