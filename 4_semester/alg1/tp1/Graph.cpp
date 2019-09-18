#include "Graph.hpp"
#include <iostream>
#include <list>
#include <vector>

// Recebe um vector de arestas e o numero de arestas
Graph::Graph(vector<Node> nodes, vector<Edge> edges, int numberOfNodes, int numberOfEdges) {
    this->edges = edges;
    this->nodes = nodes;
    this->numberOfNodes = numberOfNodes;
    this->numberOfEdges = numberOfEdges;

    // Redimensiona a lista de acordo com o numero de vertices
    // Complexidade: O(V)
    adjList = new vector<int>[numberOfNodes];

    // Percorre o vector de arestas para preencher a lista de adjacencias
    // Complexidade: O(A)
    for (Edge &edge: edges) {
        // Adiciona na lista de adjacência daquele nó o nó para o qual ele aponta
        adjList[edge.source.id].push_back(edge.destiny.id);
    }
}

Graph::~Graph() {

}

void Graph::print() {
    for (int i = 0; i < numberOfNodes; i++) {
		// print current vertex number
		std::cout << i+1 << " --> ";

		// print all neighboring vertices of vertex i
		for (int v : adjList[i])
			std::cout << v+1 << " ";
		std::cout << std::endl;
	}
}

// Função que troca a ordem de comando entre A e B (se possivel)
bool Graph::swap(int a, int b) {
    bool sucess = false;
    // Verifica se A comanda B diretamente
    if (directCommand(a,b)) {
        // Caso comande, já troca A->B para B->A
        swapCommand(a,b);
        // Se o grafo não possui ciclo após a troca
        if (!hasCycle()) {
            // trocou sem problemas
            sucess = true;
        } else {
            // problema: ocasionou ciclo. Desfaz a troca
            swapCommand(b,a);
        }
    }
    return sucess;
}

int Graph::commander(int a) {
    // Obtem os comandantes diretos de A
    vector<int> commanders = directCommanders(a);
    // Para cada um dos comandantes diretos, obtem seus comandantes diretos e faz isso recursvamente
    if(!commanders.empty()) {
        for (int i=0; i<commanders.size();i++) {
            vector otCommanders = directCommanders(commanders[i]);
        }
    } else {
        return 0;
    }
}

int Graph::commander(int a, int newAge) {
    
}

vector<int> Graph::directCommanders(int a) {
    vector<int> commanders;
    for (int i=0; i<numberOfNodes; i++) {
        for (auto it=adjList[i].begin(); it != adjList[i].end(); ++it) {
            if(*it == a) {
                commanders.push_back(i);
            }
        }
    }
    return commanders;
}

// Verifica se A comanda B diretamente
bool Graph::directCommand(int a, int b) {
    // Se B estiver na lista de adjacencia de A há conexão
    // Complexidade: Será exatamente o número de filhos/comandados de A, portanto nunca excederá o numero de vertices, sendo O(V)
    for (int node : adjList[a]) {
        // Percorre a lista de adjacencia de A
        if (node == b) {
            // B é comandado por A, havendo conexão direta A->B
            return true;
        }
    }
    return false;
}

// A->B vira B->A
void Graph::swapCommand(int a, int b) {
    auto it = adjList[a].begin(); // iterator que inicia do início do vector
    // Enquanto não estiver no fim da lista de A
    while (it != adjList[a].end()) {
        if (*it == b) {
            // remove B
            it = adjList[a].erase(it);
        } else {
            // continua
            ++it;
        }
    }
    // Adiciona A na lista de adjacencia de B (B->A)
    adjList[b].push_back(a);
}

// Verifica se há um ciclo no grafo
bool Graph::hasCycle() {
    // Marque todos os vértices como não visitados e não fazem parte da recursão
    bool *visited = new bool[numberOfNodes];
    bool *recursiveStack = new bool[numberOfNodes];
    for (int i=0; i<numberOfNodes; i++) {
        visited[i] = false;
        recursiveStack[i] = false;
    }
    // Chame a função auxiliar recursiva para detectar o ciclo em diferentes arvores DFS
    for (int i=0; i<numberOfNodes; i++) {
        if (hasCycle(i,visited,recursiveStack)) {
            return true;
        }
    }
    return false;
}

bool Graph::hasCycle(int v, bool *visited, bool *recursiveStack) {
    if (visited[v] == false) {
        visited[v] = true;
        recursiveStack[v] = true;
        vector<int>::iterator it;
        for (it = adjList[v].begin(); it != adjList[v].end(); ++it) {
            if (!visited[*it] && hasCycle(*it,visited,recursiveStack)) {
                return true;
            } else if (recursiveStack[*it]) {
                return true;
            }
        }
    }
    recursiveStack[v] = false;
    return false;
}