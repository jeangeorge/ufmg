#include "Cell.hpp"

#include <utility>

template <class T> Cell<T>::Cell() {
    this->next = nullptr;
    this->previous = nullptr;
}
template <class T> Cell<T>::~Cell() {

}

template class Cell<std::pair<int,int>>;
