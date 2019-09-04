#include "Quicksort.hpp"
#include "Insertionsort.hpp"
#include "Stack.hpp"
#include "Utils.hpp"

#include <iostream>

using std::pair;

// Inicializa as movimentações e comparações com 0
Quicksort::Quicksort() {
    this->movNumber = 0;
    this->compNumber = 0;
}

// Cada método chama a função de order passando o tipo de ordenação
void Quicksort::classic(int *array, int size) {
    this->order("QC", 0, size-1, array, size);
}
void Quicksort::medianOfThree(int *array, int size) {
    this->order("QM3", 0, size-1, array, size);
}
void Quicksort::firstElement(int *array, int size) {
    this->order("QPE", 0, size-1, array, size);
}
void Quicksort::onePercent(int *array, int size) {
    this->order("QI1", 0, size-1, array, size);
}
void Quicksort::fivePercent(int *array, int size) {
    this->order("QI5", 0, size-1, array, size);
}
void Quicksort::tenPercent(int *array, int size) {
    this->order("QI10", 0, size-1, array, size);
}

// Quicksort não recursivo feito tendo como base o algoritmo disponível nas transparências de sala
void Quicksort::nonRecursive(int *array, int size) {
    Stack<std::pair<int,int>> *stack = new Stack<std::pair<int,int>>();
    int left = 0, right = size - 1, i, j;
    std::pair<int,int> item;
    item.first = left;
    item.second = right;
    stack->insert(item);
    do {
        this->compNumber++;
        if (right > left) {
            this->compNumber++;
            this->partition("QNR",left,right,&i, &j, array);
            if ((j-left) > (right-i)) {
                item.second = j;
                item.first = left;
                stack->insert(item);
                left = i;
            }
            else {
                std::pair<int,int> item;
                item.first = i;
                item.second = right;
                stack->insert(item);
                right = j;
            }
        }
        else {
            item = stack->remove();
            right = item.second;
            left = item.first;
        }
    }while (!stack->isEmpty());
    delete stack;
}

void Quicksort::order(string type, int left, int right, int *array, int originalSize) {
    int i,j; // Índices que serão usados posteriormente
    bool needInsertion = false; // Variável para definir se é preciso chamar o método de inserção ou não

    // Avalia se é necessário chamar o método de inserção
    if (type == "QI1" || type == "QI5" || type == "QI10") {
        double percent; // Porcentagem a partir da qual devemos chamar o inserção
        int numberOfKeys = right - left + 1; // Calcula o número de chaves que estamos cobrindo nesta chamada
        // Define a porcentagem
        if (type == "QI1") {
            percent = 0.01;
        } else  if (type == "QI5") {
            percent = 0.05;
        } else {
            percent = 0.10;
        }
        // Caso tenhamos menos chaves que 1%, 5% ou 10% do total de chaves define que é necessário chamar o insertion
        if (numberOfKeys <= originalSize * percent) {
            needInsertion = true;
        }
    }

    // Caso não precise de inserção
    if (!needInsertion) {
        // Realiza o quicksort normalmente
        this->partition(type, left, right, &i, &j, array);
        this->compNumber++;
        if (left < j) {
            this->order(type, left, j, array, originalSize);
        }
        this->compNumber++;
        if (right > i) {
            this->order(type, i, right, array, originalSize);
        }
    } else {
        // Caso precise, chama o método de inserção
        int movInsertion, compInsertion; // Variáveis para armazenar o número de inserções e comparações feitas no inserção
        insertionSort(array,left,right,&movInsertion,&compInsertion); // Ordena o subvetor com o inserção
        // Atualiza o número de movimentações e comparações
        this->movNumber += movInsertion;
        this->compNumber -= compInsertion;
    }
}

void Quicksort::partition(string type, int left, int right, int *i, int *j, int *array) {
    int pivot, aux;
    *i = left; *j = right;

    // Escolhe o pivo com base no tipo do Quicksort
    if (type == "QC"  || type == "QNR") {
        // Clássico e Não-recursivo tem como pivo o elemento central
        pivot = array[(*i + *j)/2];
    } else if (type == "QPE") {
        // Primeiro elemento tem como pivo o primeiro elemento do array
        pivot = array[*i];
    } else {
        // Os demais tem como pivo o valor médio entre primeiro, central e último
        int middle = (*i + *j)/2; // Calcula a posição central
        // Sequencia de ifs para saber qual o elemento central
        // Poderia ter colocado os tres elementos num vetor e ordenado eles, mas preferi fazer assim
        if (array[left] <= array[right]) {
            if (array[middle] <= array[left]) {
                pivot = array[left];
            } else if (array[middle] >= array[right]) {
                pivot = array[right];
            } else {
                pivot = array[middle];
            }
        } else {
            if (array[middle] >= array[left]) {
                pivot = array[left];
            } else if (array[middle] <= array[right]) {
                pivot = array[right];
            } else {
                pivot = array[middle];
            }
        }
    }

    // Faz as chamadas recursivas enquanto for necessário
    while (*i <= *j) {
        while (pivot > array[*i]) {
            this->compNumber++;
            (*i)++;
        }
        while (pivot < array[*j]) {
            this->compNumber++;
            (*j)--;
        }
        this->compNumber++;
        if (*i <= *j) {
            this->compNumber++;
            if (*i < *j) {
                this->movNumber++;
                aux= array[*i]; array[*i] = array[*j]; array[*j] = aux;
            }
            (*i)++; (*j)--;
        }
        this->compNumber++;
    }
}

unsigned long long int Quicksort::getCompNumber() {
    return this->compNumber;
}

unsigned long long int Quicksort::getMovNumber() {
    return this->movNumber;
}