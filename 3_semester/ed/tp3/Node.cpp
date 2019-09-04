#include "Node.hpp"

Node::Node() {
    this->left = nullptr;
    this->right = nullptr;
    this->code = new Code();
}

Node::~Node() {

}