#ifndef TIPOS_H //If not defined
#define TIPOS_H

#include <vector>
#include <string>

using namespace std;

struct ConfiguracionMemoria {
    int tamanoPagina; //Tamano de pagina (de marco) en bytes
    int tamanoMemoriaVirtual; //en bytes
    int tamanoMemoriaFisica; //en bytes
    int numeroDePaginas; // Recordemos que numeroDePaginas = tamanoMemoriaVirtual / tamanoPagina
    int numeroDeMarcos; // Recordemos que numeroDeMarcos = tamanoMemoriaFisica / tamanoPagina
    int bitsOffset; // Bits para el offset dentro de la página
    int bitsPagina; // Bits para el número de página
    int bitsMarco;  // Bits para el número de marco
    vector <int> tablaPaginas; //El indice es el numero de pagina, y el valor es el nuemro de marco
};

struct Traduccion {
    string direccionVirtualHexadecimal;
    string direccionFisicaHexadecimal;
    string direccionFisicaBinario;
    int numPagina; //Numero de pagina extraido
    int offset; //Offset dentro de la pagina
    int numMarco; //Numero de marco asignado (de la tabla de paginas)
    int direccionFisica;
    bool valida; //Aqui nos preguntamos, fue valida la traduccion?
    string mensajeError; //Contenido del mensaje de error en caso de no ser valida

    // Bits de control
    bool bitCache;
    bool bitReferida;
    bool bitModificada;
    bool bitProteccion;
    bool bitPresente;
};

#endif