#include <iostream>

#include "Member.hpp"
#include "Node.hpp"
#include "Edge.hpp"
#include "Graph.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::vector;

// V: número de vértices, A: número de arestas

int main() {
    int members, relationships, instructions; // quantidades: nós, vertices e comandos

    cin >> members >> relationships >> instructions; // leitura das quantidades

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
        cin >> age;
        nodes[i] = Node(i,age);
    }

    // Preenche as arestas com as relações de comando
    // Complexidade: O(A)
    for (int i=0; i<relationships; i++) {
        int source, destiny;
        cin >> source >> destiny;
        edges[i] = Edge(nodes[source-1],nodes[destiny-1]); // -1 porque os ids dos membros iniciam-se no 1 e o vector começa no indice 0
    }

    // Instancia o grafo, passando as arestas, o numero de nós e o numero de arestas
    // Complexidade de construção do grafo: O(V + A)
    Graph *graph = new Graph(nodes,edges,members,relationships);

    // Inicia a leitura das instruções
    // Complexidade: Entendi que nesse laço é irrelevante, a complexidade de cada função é analisada dentro da mesma
    for (int i=0; i<instructions; i++) {
        char instruction;
        cin >> instruction;
        // swap
        if (instruction == 'S') {
            // Faz a leitura dos membros que se quer trocar
            int a,b;
            cin >> a >> b;
            if (graph->swap(a-1,b-1)) {
                cout << "S T" << endl;
            } else {
                cout << "S N" << endl;
            }
        }
        // command
        else if (instruction == 'C') {
            // Le o membro e mostra o comandante mais novo
            int a;
            cin >> a;
            cout << graph->commander(a-1) << endl;
        }
        // meeting
        else if (instruction == 'M') {
            // graph->meeting();
        }
    }

    delete graph;

    return 0;
}