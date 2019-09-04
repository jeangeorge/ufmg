#ifndef TP3_ED_TREE_HPP
#define TP3_ED_TREE_HPP

#include "Node.hpp"
#include <string>

class Tree {
    public:
        Tree();
        ~Tree();
        void printPreOrder(Node* node);
        void printPreOrder();
        bool buildTree(std::string filename);
        char decode(std::string code);
    private:
        Node* root;
        void add(Code code);
};

#endif
