#ifndef DATOS_HPP_
#define DATOS_HPP_

#include "Produccion.hpp"
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

class Datos {

public:

    ///Variables de obtención
    char Epsilon;
    char Inicio;
    std::vector<char> Terminales;
    std::vector<char> NoTerminales;
    std::vector<Produccion*> ReglasDeProduccion;

    ///Variables de generación
    std::vector<Primeros*> prims;
    std::vector<Primeros*> ults;

    Datos();
    bool Lectura(std::string Documento);
    void InfoLectura();
    void Limpiar();




};


#endif // DATOS_HPP_
