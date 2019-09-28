#ifndef NODE_HPP
#define NODE_HPP

#include <vector>

using std::vector;

// Nó
class Node {
    public:
        int id, age;

        Node(int id, int age);
        Node();
        ~Node();
};

#endif
