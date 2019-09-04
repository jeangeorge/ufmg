void insertionSort(int *array, int left, int right, int *movInsertion, int *compInsertion) {
    int i, j, aux;
    *movInsertion = 0; *compInsertion = 0; // Inicializa o número de movimentações e comparações com 0
    // Percorre o array da posição left até a posição right e ordena essa parte do array
    for (i = left; i < right; i++) {
        aux = array[i];
        j = i;
        while (j >= 0 && array[j] > aux) {
            compInsertion++;
            movInsertion++;
            array[j + 1] = array[j];
            j--;
        }
        movInsertion++;
        array[j + 1] = aux;
    }
}