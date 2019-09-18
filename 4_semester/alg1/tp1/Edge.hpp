
#ifndef EDGE_HPP
#define EDGE_HPP

#include "Node.hpp"

// Vértice
class Edge {
    public:
        Node source;
        Node destiny;

        Edge(Node source, Node destiny);
        Edge();
        ~Edge();
};

#endif
