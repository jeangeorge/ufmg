#ifndef TP2_ED_CELL_HPP
#define TP2_ED_CELL_HPP

template <class T> class Cell {
public:
    T item;
    Cell *previous,*next;
    Cell();
    ~Cell();
};

#endif
