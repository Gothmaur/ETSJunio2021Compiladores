#ifndef _PRUEBASAFN_HPP_
#define _PRUEBASAFN_HPP_

#include "AFN.hpp"
#include <string>

class PruebasAFN{
public:
  bool noEsEspecial(char a);
  AFN convertirERaAFN(std::string expresionRegular);
};

#endif
