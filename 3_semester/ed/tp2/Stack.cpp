#include "Stack.hpp"
#include "Cell.hpp"

#include <utility>

template <class T> Stack<T>::Stack() {
    this->top = nullptr;
}

template <class T> Stack<T>::~Stack() {
    delete this->top;
}

template <class T> bool Stack<T>::isEmpty() {
    return this->top == nullptr;
}

// Insere no topo da pilha
template <class T> void Stack<T>::insert(T newItem) {
    Cell<T> *cell = new Cell<T>();
    cell->item = newItem;
    if (this->top != nullptr) {
        this->top->next = cell;
    }
    cell->previous = this->top;
    this->top = cell;
}

// Remove do topo da pilha e retorna o elemento removido
template <class T> T Stack<T>::remove() {
    Cell<T> *cell = this->top;
    if (this->top->previous != nullptr) {
        this->top = this->top->previous;
        this->top->next = nullptr;
    } else {
        this->top = nullptr;
    }
    cell->previous = nullptr;
    T item = cell->item;
    delete cell;
    return item;
};

template class Stack<std::pair<int,int>>;
