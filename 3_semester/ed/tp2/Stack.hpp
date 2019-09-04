#ifndef TP2_ED_STACK_HPP
#define TP2_ED_STACK_HPP

#include "Cell.hpp"
#include <utility>

// Pilha que será utilizada no quicksort não recursivo
template <class T> class Stack {
    public:
        Cell<T> *top;

        Stack();
        ~Stack();
        bool isEmpty();
        void insert(T newItem);
        T remove();
};

#endif


