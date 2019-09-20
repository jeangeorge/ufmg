#include "Graph.hpp"
#include <iostream>
#include <queue>
#include <vector>

// Recebe um vector de arestas e o numero de arestas
Graph::Graph(vector<Node> nodes, vector<Edge> edges, int numberOfNodes, int numberOfEdges) {
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

     for (int i=0; i<topOrder.size(); i++)
        std::cout << topOrder[i]+1 << " ";
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
    // Marca todos os vértices como não visitados e não fazem parte da recursão
    bool *visited = new bool[numberOfNodes];
    bool *recursiveStack = new bool[numberOfNodes];
    for (int i=0; i<numberOfNodes; i++) {
        visited[i] = false;
        recursiveStack[i] = false;
    }
    // Chama a função auxiliar recursiva para detectar o ciclo em diferentes arvores DFS
    for (int i=0; i<numberOfNodes; i++) {
        if (hasCycle(i,visited,recursiveStack)) {
            return true;
        }
    }
    return false;
}


bool Graph::hasCycle(int v, bool *visited, bool *recursiveStack) {
    // Se o vértice ainda não foi visitado
    if (visited[v] == false) {
        // Visita ele
        visited[v] = true;
        recursiveStack[v] = true;
        vector<int>::iterator it;
        // Percorre os adjacentes de v
        for (it = adjList[v].begin(); it != adjList[v].end(); ++it) {
            if (!visited[*it] && hasCycle(*it,visited,recursiveStack)) {
                // Se ele ainda não foi visitado e possui ciclo: grafo possui ciclo
                return true;
            } else if (recursiveStack[*it]) {
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
    this->adjList = newAdjList;
}


// Retorna uma lista contendo todos os nós conectados a A
vector<Node> Graph::connected(int a) {
    int first = a; // Primeiro nó (para evitar armazenar o proprio no na lista bfs)
    vector<Node> connectedNodes;
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
        for (auto i = adjList[a].begin(); i != adjList[a].end(); ++i)
        {
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
    // Cria um vector de ints
    vector<int> in_degree(numberOfNodes, 0);

    // Traverse adjacency lists to fill indegrees of
    // vertices.  This step takes O(V+E) time
    for (int u=0; u<numberOfNodes; u++) {
        vector<int>::iterator itr;
        for (itr = adjList[u].begin(); itr != adjList[u].end(); itr++)
             in_degree[*itr]++;
    }

    // Create an queue and enqueue all vertices with
    // indegree 0
    std::queue<int> q;
    for (int i = 0; i < numberOfNodes; i++)
        if (in_degree[i] == 0)
            q.push(i);

    // Initialize count of visited vertices
    int cnt = 0;

    // Create a vector to store result (A topological
    // ordering of the vertices)
    vector <int> top_order;

    // One by one dequeue vertices from queue and enqueue
    // adjacents if indegree of adjacent becomes 0
    while (!q.empty()) {
        // Extract front of queue (or perform dequeue)
        // and add it to topological order
        int u = q.front();
        q.pop();
        top_order.push_back(u);

        // Iterate through all its neighbouring nodes
        // of dequeued node u and decrease their in-degree
        // by 1
        vector<int>::iterator itr;
        for (itr = adjList[u].begin(); itr != adjList[u].end(); itr++)

            // If in-degree becomes zero, add it to queue
            if (--in_degree[*itr] == 0)
                q.push(*itr);

        cnt++;
    }

    return top_order;
}