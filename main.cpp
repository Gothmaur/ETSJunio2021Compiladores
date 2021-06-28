/******************************************
* Alumno: Mauricio Alejandro Trejo Miranda*
* Proyecto: ETS de compiladores 2021      *
* correo: mtrejom1501@alumno.ipn.mx       *
******************************************/

///Bibliotecas base
#include <iostream>
#include <cstring>
#include <stdlib.h>

///Bibliotecas creadas en clase
#include "Encabezados/PruebasAFD.hpp"
#include "Encabezados/PruebasAFN.hpp"
#include "Encabezados/Subconjunto.hpp"

using namespace std;

int main()
{
  ///Definición de Variables
  char tipoAutomata, opcion; ///Variables de opcion
  PruebasAFN *p1 = new PruebasAFN(); ///Puntero para probar el AFN
  PruebasAFD *afd=new PruebasAFD(); ///Puntero para el AFD de la construcción de Thompson
  Subconjunto *s = new Subconjunto(); ///Puntero para probar el algoritmo de sub conjuntos
  string cadena; ///Cadena que servirá para obtener la Exp Reg
  AFN afn; /// Auxiliar para generar el documento AFN

  ///MENÜ principal
  while(opcion != 'n'){
     system("cls");
     cout << "Ingrese el tipo de automata que desea crear:" << endl;
     cout << "1 --- ER a AFN (Contrucciones de Thompson)" << endl;
     cout << "2 --- AFN a AFD (Algoritmo de los Subconjuntos)" << endl;
     cout << "3 --- Salir del programa" <<endl;
     cout << "Ingrese su seleccion: ";
     cin >> tipoAutomata;

     ///ACCIONES
     switch(tipoAutomata){
       case '1': ///Caso 1, construir AFN por construcciones de Thompson
        cout << "Ingresa una ER: ";
        cin >> cadena;
        afn = p1->convertirERaAFN(cadena); ///Proceso de construcción
        afn.generarArchivoAFN(afn); ///Generación de documeto
        ///p1->probarCadenasAFN(afn); ///Prueba de recorrido
        break;
      case '2':
        s->iniciarAlgoritmo();
        afd->crearAFD();
        break;
      case '3':
        cout<<"Esta seguro de salir (s/n)"<<endl;
        cin >> opcion;
            if(opcion == 's') {return 0;}
        break;
       default:
        cout << "Opcion no valida" << endl;
     }
     cout << "Desea volver al menu principal? (s/n):" << endl;
     cin >> opcion;
  }
	return 0;
}
