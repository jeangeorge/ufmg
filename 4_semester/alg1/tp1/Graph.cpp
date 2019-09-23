#include "Graph.hpp"
#include <iostream>
#include <vector>
#include <algorithm>

// Recebe um vector de nós, de arestas e as quantidades
Graph::Graph(vector<Node> nodes, vector<Edge> edges, int numberOfNodes, int numberOfEdges) {
    this->nodes = nodes;
    this->numberOfNodes = numberOfNodes;
    this->numberOfEdges = numberOfEdges;

    // Redimensiona a lista de acordo com o numero de vertices
    // Complexidade: O(V)
    adjList = new vector<int>[numberOfNodes];

    // Percorre o vector de arestas para preencher a lista de adjacencias
    // Complexidade: O(A)
    for (auto edge: edges) {
        // Adiciona na lista de adjacência daquele nó o nó para o qual ele aponta
        adjList[edge.source.id].push_back(edge.destiny.id);
    }
}


Graph::~Graph() {

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


// Obtem o comandante mais novo de A
int Graph::commander(int a) {
    int lowestAge = 9999999;
    // Primeiramente transpõe o grafo
    this->transpose();
    // Obtém todos os vértices acessíveis a partir de A
    vector<Node> connectedNodes = connected(a);
    // Transpõe o grafo novamente, para voltar ao estado original
    this->transpose();
    // Verifica se a lista não está vazia
    if (!connectedNodes.empty()) {
        // Agora basta buscar a menor idade no array
        for (auto node : connectedNodes) {
            if (node.age < lowestAge) {
                lowestAge = node.age;
            }
        }
    } else {
        // Caso a lista esteja vazia, não possui nós. Nesse caso vamos retornar -1
        lowestAge = -1;
    }
    return lowestAge;
}

// Ordem das falas na reunião
void Graph::meeting() {
    // Meeting feito baseando-se na ordem topologica
    vector<int> topOrder = topologicalOrder();

    // Imprime a ordem topológica
    for (unsigned int i=0; i<topOrder.size(); i++) {
        std::cout << topOrder[i]+1 << " ";
    }
}


// Verifica se A comanda B diretamente
bool Graph::directCommand(int a, int b) {
    // Se B estiver na lista de adjacencia de A há conexão
    // Complexidade: Será exatamente o número de filhos/comandados de A, portanto nunca excederá o numero de vertices, sendo O(V)
    for (auto node : adjList[a]) {
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
    // Marca todos os vértices como não visitados e não fazem parte da recursão
    bool *visited = new bool[numberOfNodes];
    bool *recursiveStack = new bool[numberOfNodes];
    for (int i=0; i<numberOfNodes; i++) {
        visited[i] = false;
        recursiveStack[i] = false;
    }
    // Chama a função auxiliar recursiva para detectar o ciclo em diferentes arvores DFS
    for (int i=0; i<numberOfNodes; i++) {
        if (hasCycleAux(i,visited,recursiveStack)) {
            return true;
        }
    }
    return false;
}


bool Graph::hasCycleAux(int v, bool *visited, bool *recursiveStack) {
    // Se o vértice ainda não foi visitado
    if (visited[v] == false) {
        // Visita ele
        visited[v] = true;
        recursiveStack[v] = true;
        // Percorre os adjacentes de v
        for (auto i = adjList[v].begin(); i != adjList[v].end(); ++i) {
            if (!visited[*i] && hasCycleAux(*i,visited,recursiveStack)) {
                // Se ele ainda não foi visiado e possui ciclo: grafo possui ciclo
                return true;
            } else if (recursiveStack[*i]) {
                // Se não está na pilha de recursão: possui ciclo
                return true;
            }
        }
    }
    // Tira da pilha de recursão
    recursiveStack[v] = false;
    return false;
}


// Função para transpor o grafo atual
void Graph::transpose() {
    // Nova lista de adjencias
    vector<int> *newAdjList = new vector<int>[numberOfNodes];
    // Preenche a lista com o sentido invertido
    for (int i=0; i<numberOfNodes; i++) {
        for (int j : adjList[i]) {
            newAdjList[j].push_back(i);
        }
    }
    // Troca a lista de adjacencias
    this->adjList = newAdjList;
}


// Retorna uma lista contendo todos os nós conectados a A
vector<Node> Graph::connected(int a) {
    int first = a; // Primeiro nó (para evitar armazenar o proprio no na lista bfs)
    vector<Node> connectedNodes; // Vector onde armazerá os nós

    // Seta todos os nós como não visitados
    bool visited[numberOfNodes];
    for(int i = 0; i < numberOfNodes; i++)
        visited[i] = false;

    // Estrutura para o BFS
    vector<int> queue;

    // Marca o nó de origem como visitado e coloca na lista
    visited[a] = true;
    queue.push_back(a);

    // Enquanto há elementos na fila
    while(!queue.empty()) {
        // Pega o último elemento
        a = queue.back();
        // Se não for o primeiro (A), coloca na lista de nós conectados
        if (a != first) {
            connectedNodes.push_back(nodes[a]);
        }

        // Remove do fim
        queue.pop_back();

        // Percorre todos os vértices adjacentes a A.
        for (auto i = adjList[a].begin(); i != adjList[a].end(); ++i) {
            // Se o adjacente não foi visitado
            if (!visited[*i]) {
                // O visita e o adiciona na lista
                visited[*i] = true;
                queue.push_back(*i);
            }
        }
    }

    return connectedNodes;
}

vector<int> Graph::topologicalOrder() {
    vector<int> stack; // Estrutura que armazenaremos a ordem, alterada pela função recursiva
    // Marque  todos os nós como não visitados
    bool visited[numberOfNodes];
    for (int i=0; i<numberOfNodes; i++) {
        visited[i] = false;
    }

    // Chama a função recursiva para guardar a ordem topologica
    for (int i=0; i<numberOfNodes; i++) {
        if (!visited[i]) {
            topologicalOrderAux(i, visited, stack);
        }
    }

    std::reverse(stack.begin(),stack.end());
    // Retorna a ordem topologica
    return stack;
}

void Graph::topologicalOrderAux(int v, bool* visited, vector<int> &stack) {
    // Visita o nó atual
    visited[v] = true;

    // Percorre a lista de adjacencia de v
    for (auto i=adjList[v].begin(); i!=adjList[v].end(); i++) {
        // Se o vertice i, comandado por v, ainda não foi visitado
        if (!visited[*i]) {
            // Pega sua ordem topologica
            topologicalOrderAux(*i,visited,stack);
        }
    }

    // Coloca v na pilha
    stack.push_back(v);
}