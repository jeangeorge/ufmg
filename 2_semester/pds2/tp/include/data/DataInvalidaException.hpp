#include <exception>

class DataInvalidaException: public std::exception {
    public:
        virtual const char* what() const throw () {
            return "Erro: Data invalida.";
        }
};