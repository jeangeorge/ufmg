#define NUM_TESTS 21

#include "Utils.hpp"
#include "Quicksort.hpp"

#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <chrono>
#include <string>

using namespace std;
using namespace std::chrono;

int main(int argc, char *argv[]) {
    string quick_type, order_type, aux; // Tipo do quicksort, do vetor e uma variavel auxiliar
    int size; // Tamanho do vetor
    bool show; // Variável para controlar se será necessário mostrar o vetor ou não
    int times[NUM_TESTS]; // Vetor que será utilizado para armazenar os tempos
    auto *utils = new Utils(); // Variável de funções úteis
    auto *quicksort = new Quicksort(); // Objeto quicksort
    stringstream history; // Variável para armazenar os vetores em formato de string posteriormente

    // Define o tipo do quicksort, o tipo do vetor e seu tamanho
    quick_type = argv[1];
    order_type = argv[2];
    size = stoi(argv[3]);

    // Define se será necessário mostrar os vetores utilizados
    if (argv[4]) {
        aux = argv[4];
    } else {
        aux = "";
    }
    show = !aux.compare("-p");

    // Loop para repetir o processo de ordenação NUM_TESTS vezes
    for (int i = 0; i < NUM_TESTS; i++) {
        int array[size]; // Array do tamanho recebido

        // Avalia qual o tipo de array deve ser gerado
        if (order_type == "OrdC") {
            utils->ascArray(array, size);
        } else if (order_type == "OrdD") {
            utils->descArray(array, size);
        } else {
            utils->randomArray(array, size);
        }

        // Armazena o array gerado na stream
        history << utils->arrayToString(array, size) << "\n";

        // Pega o horário do sistema antes da execução da ordenação
        // O tempo é medido a partir daqui porque nos interessa saber quanto tempo demoram os métodos de ordenação
        high_resolution_clock::time_point t1 = high_resolution_clock::now();

        // Chama a função de ordenação correta
        if (quick_type == "QC") {
            quicksort->classic(array, size);
        } else if (quick_type == "QM3") {
            quicksort->medianOfThree(array, size);
        } else if (quick_type == "QPE") {
            quicksort->firstElement(array, size);
        } else if (quick_type == "QI1") {
            quicksort->onePercent(array, size);
        } else if (quick_type == "QI5") {
            quicksort->fivePercent(array, size);
        } else if (quick_type == "QI10") {
            quicksort->tenPercent(array, size);
        } else if (quick_type == "QNR") {
            quicksort->nonRecursive(array, size);
        }

        // Pega o horario do sistema depois da execução da ordenação
        high_resolution_clock::time_point t2 = high_resolution_clock::now();

        // Obtem a diferenca entre o horario de fim e o de inıcio em microssegundos
        duration<double, micro> elapsed_time = duration_cast<duration<double>>(t2 - t1);

        // Armazena o resultado no array de tempo
        times[i] = (int)round(elapsed_time.count());
    }

    // Ordeno o vetor de tempo usando o quicksort mediana de 3 (para evitar um possível pior caso)
    quicksort->medianOfThree(times, NUM_TESTS);

    // Mostra o tipo do quicksort, o tipo do vetor, tamanho do vetor, média do número de comparações, média do número de movimentações e a mediana do tempo
    cout << quick_type << " " << order_type << " " << size << " " << quicksort->getCompNumber() / NUM_TESTS << " " << quicksort->getMovNumber() / NUM_TESTS << " " << times[NUM_TESTS/2] << endl;

    // Caso seja necessário mostrar os arrays, printa-os
    if (show) {
        cout << history.str() << endl;
    }

    // Desaloca a memória dos objetos e finaliza o programa
    delete quicksort;
    delete utils;

    return 0;
}