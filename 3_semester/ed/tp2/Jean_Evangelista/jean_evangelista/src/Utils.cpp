#include "Utils.hpp"
#include <random>
#include <chrono>
#include <iostream>
#include <sstream>

using std::uniform_int_distribution;
using std::string;

std::default_random_engine dre (std::chrono::steady_clock::now().time_since_epoch().count());

// Gerador de número de aleatório no intervalo [0, max]
int Utils::randomNumber(int max) {
    uniform_int_distribution<int> uid {0, max};
    return uid(dre);
}

// Gerador de array crescente
void Utils::ascArray(int *array, int size) {
    for (int i=0;i<size;i++) {
        array[i] = i;
    }
}

// Gerador de array decrescente
void Utils::descArray(int *array, int size) {
    int j = 0;
    for (int i=size-1;i>=0;i--) {
        array[j] = i;
        j++;
    }
}

// Gerador de array aleatório
void Utils::randomArray(int *array, int size) {
    for (int i=0; i<size; i++) {
        array[i] = randomNumber(size);
    }
}

// Conversor de array para string
string Utils::arrayToString(int *array, int size) {
    std::stringstream ss;
    for (int i=0; i<size; i++) {
        ss << array[i] << " ";
    }
    ss << "\n";
    return ss.str();
}