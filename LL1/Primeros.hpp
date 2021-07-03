#ifndef PRIMEROS_HPP_
#define PRIMEROS_HPP_

#include <vector>
#include <string>

class Primeros {
public:

   char Simbolo; //Simbolo productor
   std::vector<char> prod; //Producción

  Primeros(char);
  void AgregarPrimero(char simbolo);
};

#endif // PRIMEROS_HPP_
