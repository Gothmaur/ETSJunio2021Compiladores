#include "Datos.hpp"

/**
 * Constructor
 * **/
 Datos::Datos(){};

/**
    * Esta funci�n realiza la lectura de datos desde un archivo
    * para una gramatica libre de contexto
    * Entrada: Gramatica, url de documento
    * Salida: 1 si se obtienen los datos correctamente,
    *         0 si ocurri� un error con la lectura
*/
 bool Datos::Lectura(std::string Documento){
    ifstream archivo(Documento); ///Abrir archivo
    if(archivo.is_open()){
        std::string aux;
        getline(archivo,aux); //Obtiene primer linea del documento
        if(aux.length() == 0){ return 0;}// return 0 si no se encontro axioma o simbolo inicial
        Inicio = aux[0];//Almacena el simbolo inicial
        getline(archivo,aux);
        if(aux.length() == 0){ return 0;} //return 0 si no se encontraron datos no terminales
        for(unsigned int i=0; i<aux.length(); i+=2){
            NoTerminales.reserve(1); //Reserva y guarda cada simbolo no terminal
            NoTerminales.push_back(aux[i]);
        }
        getline(archivo,aux);
        if(aux.length() == 0){ return 0; } //return archivo si no se encontraron datos Terminales
        for(unsigned int i=0; i<aux.length(); i+=2){
            Terminales.reserve(1); //Reserva y guarda cada simbolo no terminal
            Terminales.push_back(aux[i]);
        }
        getline(archivo,aux);
        if(aux.length() == 0){ return 0; } //return 0 si no se encontraron producciones
        do{
            char simbolo = aux[0]; //obtencion del simbolo
            string prod = aux.substr(5,aux.length()); //obtencion de valor de produccion
            ReglasDeProduccion.reserve(1);
            ReglasDeProduccion.push_back(new Produccion(simbolo,prod));//Agregando producci�n a la lista
        }while(getline(archivo,aux));
        return 1;
    }else{ return 0; } //Return 0 si no se abri� el archivo
 }

void Datos::InfoLectura()
{
    cout << "Inicio: " << Inicio <<endl; //Mostrar simbolo inicial
    cout << "No terminales: " << endl; //Mostrar simbolos no terminales
    for(unsigned int i=0; i<NoTerminales.size(); i++){
        cout << NoTerminales[i];
        if(i < NoTerminales.size()-1){ cout <<",";}
    }
    cout << endl;
    cout << "Terminales: " << endl; //Mostrar simblos Terminales
    for(unsigned int i=0; i<Terminales.size(); i++){
        cout << Terminales[i];
        if(i<Terminales.size()-1){ cout <<",";}
    }
    cout <<endl;
    cout << "Reglas de producci�n: " << endl; //Mostrar simblos Terminales
    for(unsigned int i=0; i < ReglasDeProduccion.size(); i++){
        cout << ReglasDeProduccion[i]->Simbolo << " -> " << ReglasDeProduccion[i]->prod <<endl;
    }
}

void Datos::Limpiar(){
    Terminales.clear();
    NoTerminales.clear();
    ReglasDeProduccion.clear();
    for(unsigned int i=0; i < prims.size(); i++){
        prims[i]->prod.clear();
    }
    prims.clear();for(unsigned int i=0; i < ults.size(); i++){
        ults[i]->prod.clear();
    }
    ults.clear();
}
