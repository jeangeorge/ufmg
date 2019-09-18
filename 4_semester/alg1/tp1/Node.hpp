#ifndef NODE_HPP
#define NODE_HPP

#include "Member.hpp"
#include <vector>

using std::vector;

// Nó
class Node {
    public:
        int id, age;

        Node(int id, int age); // Constutor do nó recebe o membro a ser inserido
        Node();
        ~Node();
};

#endif
