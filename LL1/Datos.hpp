#ifndef DATOS_HPP_
#define DATOS_HPP_

#include "Produccion.hpp"
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

class Datos {

public:

    char Epsilon;
    char Inicio;
    std::vector<char> Terminales;
    std::vector<char> NoTerminales;
    std::vector<Produccion*> ReglasDeProduccion;

    Datos();
    bool Lectura(std::string Documento);
    void InfoLectura();




};


#endif // DATOS_HPP_
