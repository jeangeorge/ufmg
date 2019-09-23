
#ifndef EDGE_HPP
#define EDGE_HPP

#include "Node.hpp"

// Vértice - Tem um nó de origem e um nó de destino
class Edge {
    public:
        Node source;
        Node destiny;

        Edge(Node source, Node destiny);
        Edge();
        ~Edge();
};

#endif
