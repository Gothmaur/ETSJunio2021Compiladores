#include "PruebasAFD.hpp"

/**
 * Esta funcion permite crear un AFD a partir de un archivo
 * **/
void PruebasAFD::crearAFD(){
    AFD afd("afd.txt","AFD");
    afd.toString("AFD");
}
