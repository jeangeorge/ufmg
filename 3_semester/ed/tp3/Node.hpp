//
// Created by jeang on 30/06/2019.
//

#ifndef TP3_ED_NODE_HPP
#define TP3_ED_NODE_HPP

#include "Code.hpp"

class Node {
    public:
        Node* left;
        Node* right;
        Code* code;

        Node();
        ~Node();
};

#endif //TP3_ED_NODE_HPP
