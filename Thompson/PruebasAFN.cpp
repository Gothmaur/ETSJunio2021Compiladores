#include "PruebasAFN.hpp"

/**
 * Esta funcion comprueba que un caracter no sea el caracter
 * nulo o alguno de los caracteres especiales utilizados para
 * definir expresiones regulares.
 * Recibe:
 *  - char a :: caracter a evaluar
 * Regresa:
 *  - true :: si el caracter no pertenece a un operador de ER o el caracter nulo
 *  - false :: si es un operador de ER o es el caracter nulo
 * **/
bool PruebasAFN::noEsEspecial(char a){
  switch(a){
    case 0: return false; // Caracter nulo
    case 40: return false;  // (
    case 41: return false;  // )
    case 42: return false;  // *
    case 43: return false;  // +
    case 124: return false; // |
    default: return true;
  }
}


/**
 * Esta funcion permite convertir una expresion regular en un AFN
 * usando las construcciones de Thompson.
 * Recibe:
 *  - string expresionRegular :: cadena que representa a la expresion regular
 * Regresa:
 *  AFN afn :: El automata finito no determinista que reconoce el lenguaje
 *             generado por la expresion regular, hecho mediante las construcciones
 *             de Thompson.
 * **/
AFN PruebasAFN::convertirERaAFN(string expresionRegular){
  AFN afn;  // AFN principal
  string subexpresion; // Subexpresion que se encuentre dentro de un parenstesis
  int i = 0; // Contador para movernos sobre la cadena
  int j;  // Contador auxiliar
  int balanceo = 0; // Bandera para manejar el balanceo de parentesis
  int cadlen = expresionRegular.size(); //Tamanio de la cadena
  bool parentesis = true; // B andera para saber si termino el balanceo
  while(i < cadlen){  // Loop sobre la cadena
    balanceo = 0;
    parentesis = true;
    j=0;
    if(expresionRegular[i] == '('){ // Se encuentra un parentesis
      j = i + 1;  // Guardamos la posicion a partir del siguiente caracter
      balanceo++; // Incrementamos el contador de balanceo
      while(parentesis && j < cadlen){  // Buscamos el parentesis de cierre para generar una subexpresión
        if(expresionRegular[j] == ')'){
          balanceo--;
          if(balanceo == 0){ // Si ya esta balanceado
            parentesis = false; // Termina el loop
          }
        }
        else if(expresionRegular[j] == '('){
          balanceo++; // Incrementamos el contador de balanceo
        }
        j++;
      }
      subexpresion = expresionRegular.substr(i+1,j-2-(i)); // Guardamos la subexpresion contenida en losw parentesis
      AFN subAfn = convertirERaAFN(subexpresion); // Se crea el AFN de la subexpresion
      if(j < cadlen){
        if(expresionRegular[j] == '*'){ // Si a lo que esta entre parentesis le sigue una cerradura de Kleen
          afn.aplicarCerraduraKleenAFN(&subAfn); // Se le aplica la cerradura
          j++;
        }
        else if(expresionRegular[j] == '+'){  // Si es una cerradura positiva
          afn.aplicarCerraduraPositivaAFN(&subAfn); // Se le aplica la cerradura
          j++;
        }
      }
      afn.copiarAlfabeto(&afn,subAfn); // Copiamos el alfabeto del subAfn al afn
      int numeroDeEstados = afn.automata_estados.size();
      afn.eliminarEstadoFinal(&afn);  // Eliminamos el estado final del afn
      Estado * estado = subAfn.obtenerEstadoInicial(); // Obtenemos el estado inicial del subafn
      if((int)afn.automata_estados.size()==0){  // Si el afn no tiene estados
        afn.automata_estadoInicial = subAfn.automata_estadoInicial; // El inicial del afn es el inicial del subAfn
      }
      else{
        if(estado->numeroDeEstado != 0){ // Si el numero del estado inicial del subAfn no es cero
          subAfn.renumerarEstado(&subAfn,0,estado->numeroDeEstado); // Renumeramos el estado 0 al numero del estado inicial
          subAfn.renumerarEstado(&subAfn,estado->numeroDeEstado,0); // Renumeramos el estado inicial a 0
          subAfn.swapTransiciones(&subAfn,estado->numeroDeEstado,0); // Intercambiamos las transiciones
        }
        subAfn.renumerarEstados(&subAfn, numeroDeEstados-1); // Renumeramos los estados del subAfn para evitar duplicaciones
        subAfn.modificarTransiciones(&subAfn,0,numeroDeEstados-1); // Las transiciones del estado inicial del subAfn se le asignan al final del afn
        subAfn.eliminarEstadoInicial(&subAfn); // Eliminamos el estado inicial del subAfn
      }
      afn.agregarEstados(&afn, subAfn.automata_estados); // Se agregan los estados del subAfn al afn
      afn.agregarTransiciones(&afn, subAfn.automata_tablaDeTransiciones); // Se agregan las transiciones del subAfn al afn
      afn.automata_estadoFinal = subAfn.automata_estadoFinal; // El estado final del afn, es el final del subAfn
      i += (j-i);
    }
    if(expresionRegular[i] == '|'){ // Si es el operador de union
      AFN subAfnUnion;
      /* Se crea el subAfn de la subexpresión que le sigue al operador de union '|' */
      subAfnUnion = convertirERaAFN(expresionRegular.substr(i+1,expresionRegular.size()-1));
      afn.unir(&afn,subAfnUnion); // Unimos ambos automatas
      afn.copiarAlfabeto(&afn,subAfnUnion); // Copiamos el alfabeto del subAfn al afn
      i=expresionRegular.size();
    }
    else if(noEsEspecial(expresionRegular[i])){ // Si no es ninguno de los operadores de ER
      bool esEpsilon = false; // Bandera para saber si es una transicion epsilon
      if(expresionRegular[i]=='E'){ // Si el caracter corresponde a epsilon
        esEpsilon = true;
      }
      if(i < cadlen - 1 ){ //Si no es el último caracter
        if(expresionRegular[i+1]=='*'){ // Si el siguiente caracter es una cerradura de Kleen
          afn.aplicarCerraduraKleen(&afn,expresionRegular[i],esEpsilon);
          afn.agregarSimboloAlAlfabeto(&afn,expresionRegular[i]);
          i+=2;
        }
        else if(expresionRegular[i+1]=='+'){  // Si el siguiente caracter es una cerradura positiva
          afn.aplicarCerraduraPositiva(&afn,expresionRegular[i],esEpsilon);
          afn.agregarSimboloAlAlfabeto(&afn,expresionRegular[i]);
          i+=2;
        }
        else{ // Si no es cerradura, solo se concatena
          afn.concatenar(&afn,expresionRegular[i],esEpsilon);
          afn.agregarSimboloAlAlfabeto(&afn,expresionRegular[i]);
          i++;
        }
      }
      else{ // Concatenacion
        afn.concatenar(&afn,expresionRegular[i],esEpsilon);
        afn.agregarSimboloAlAlfabeto(&afn,expresionRegular[i]);
        i++;
      }
    }
  }
  return afn; // Se regresa el afn de la expresion regular
}
