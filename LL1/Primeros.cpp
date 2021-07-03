#include "Primeros.hpp"

/**
    *Constructor
*/
Primeros::Primeros(char s){
    Simbolo = s;
};

void Primeros::AgregarPrimero(char c){
    prod.reserve(1);
    prod.push_back(c);
}
