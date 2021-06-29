#ifndef _PRUEBASAFN_HPP_
#define _PRUEBASAFN_HPP_

#include "Pruebas.hpp"
#include "AFN.hpp"
#include <string>

class PruebasAFN : public Pruebas{
public:
  std::vector<Transicion*> definirTransicionesAFN(int numeroDeTransiciones, std::vector<char> alfabeto);
  bool noEsEspecial(char a);
  AFN convertirERaAFN(std::string expresionRegular);
};

#endif
