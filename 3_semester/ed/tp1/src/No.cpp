#include "Curso.hpp"
#include "Candidato.hpp"
#include "No.hpp"

template <class T> No<T>::No() {
	proximo = nullptr;
}

template <class T> No<T>::~No() {

}

template class No<Curso>;
template class No<Candidato>;
