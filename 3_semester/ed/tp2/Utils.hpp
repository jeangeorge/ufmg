#ifndef TP2_ED_UTILS_HPP
#define TP2_ED_UTILS_HPP

#include <string>

using std::string;

// Classe para realizar operações e tarefas usuais
class Utils{
    public:
        void ascArray(int *array, int size);
        void descArray(int *array, int size);
        void randomArray(int *array, int size);
        string arrayToString(int *array, int size);
    private:
        int randomNumber(int max);
};

#endif
