#ifndef _AFD_HPP_
#define _AFD_HPP_

#include "Automata.hpp"

class AFD : public Automata{
public:
  AFD(std::string archivo, std::string tipo):Automata(archivo, tipo){};
};

#endif
