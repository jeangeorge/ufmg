#ifndef TP2_ED_QUICKSORT_HPP
#define TP2_ED_QUICKSORT_HPP

#include <string>

using std::string;

class Quicksort{
    public:
        Quicksort();
        void classic(int *array, int size);
        void medianOfThree(int *array, int size);
        void firstElement(int *array, int size);
        void onePercent(int *array, int size);
        void fivePercent(int *array, int size);
        void tenPercent(int *array, int size);
        void nonRecursive(int *array, int size);
        unsigned long long int getMovNumber();
        unsigned long long int getCompNumber();
    private:
        void order(string type, int left, int right, int *array, int originalSize);
        void partition(string type, int left, int right, int *i, int *j, int *array);
        unsigned long long int movNumber;
        unsigned long long int compNumber;
};

#endif
