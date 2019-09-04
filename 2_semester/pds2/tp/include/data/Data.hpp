#ifndef DATA_H
#define DATA_H

#include "DataInvalidaException.hpp"

#include <iostream>
#include <string>

using std::ostream;

class Data {
    friend ostream &operator<<(ostream &, const Data &);

    public:
        Data();
        Data(int dia, int mes, int ano);

        void setData(int, int, int);
        Data &operator++();  // operador prefixo de incremento
        Data operator++(int);  // operador posfixo de incremento
        const Data &operator+=(int);  // adiciona dias
        bool anoBissexto(int) const;  // ano bissexto?
        bool fimDoMes(int) const;  // fim do mes?
        int getMes() const;
        int getDia();
        int getMesValor();
        int getAno();
    private:
        int mes;
        int dia;
        int ano;
        static const int dias[];
        void auxiliaIncremento();  // funcao auxiliar no incremento da data
};

#endif
