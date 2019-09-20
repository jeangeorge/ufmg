
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "Node.hpp"
#include "Edge.hpp"

#include <vector>

using std::vector;

// Grafo
class Graph {
    public:
        int numberOfNodes; // Numero de nos que o grafo possui
        int numberOfEdges; // Numero de arestas do grafo

        Graph(vector<Node> nodes, vector<Edge> edges, int numberOfNodes, int numberOfEdges); // Construtor: recebe um vector de vertices, o numero de nós e arestas
        ~Graph(); // Destrutor

        bool swap(int a, int b); // Função para trocar a relação de comando a -> b, a e b são os ids dos membros/alunos
        int commander(int a); // Retorna a idade da pessoa mais nova que comanda A
        void meeting(); // Mostra uma ordem de fala possivel

        void print();
    private:
        vector<int> *adjList; // Lista de adjacencia do grafo: array de vectors {{1,2},{3,4}} etc
        vector<Node> nodes; // Lista de nós

        bool directCommand(int a, int b); // Verifica se A comanda B diretamente
        void swapCommand(int a, int b); // Troca A->B para B->A
        bool hasCycle(); // Verifica se o grafo possui ciclo
        bool hasCycle(int v, bool *visited, bool *recursiveStack);
        void transpose(); // Transpõe o grafo
        vector<Node> connected(int a); // Retorna todos os vertices conectados a A
        vector<int> topologicalOrder(); // Retorna uma lista de vértices em ordem topológica
};

#endif
