#include "archivo.h"
#include <fstream>
#include <iostream>
#include <cmath>

using namespace std;

int calcularBits(int n) {
    int bits=0;
    while((n >>= 1) >= 1){
        bits++;
    }
    return bits;
}

bool leerArchivo(const string & nombreArchivo, ConfiguracionMemoria & config){
    ifstream archivo(nombreArchivo);

    if( !(archivo.is_open()) ){
        cout << "Error: No se pudo abrir el archivo '" << nombreArchivo << "'" << "\n";
        return false;
    }

    archivo >> config.tamanoPagina;
    archivo >> config.tamanoMemoriaVirtual;
    archivo >> config.tamanoMemoriaFisica;

    config.numeroDePaginas = config.tamanoMemoriaVirtual / config.tamanoPagina;
    config.numeroDeMarcos = config.tamanoMemoriaFisica / config.tamanoPagina;
    config.bitsOffset = calcularBits(config.tamanoPagina);
    config.bitsPagina = calcularBits(config.numeroDePaginas);
    config.bitsMarco = calcularBits(config.numeroDeMarcos);

    // Leemos la tabla de páginas. Cada número que leemos es el marco asignado a esa página
    int valor;
    while (archivo >> valor) {
        config.tablaPaginas.push_back(valor);
    }
    archivo.close();

    //Checamos que la tabla tenga la misma cantidad de entradas que de paginas
    if ((int)config.tablaPaginas.size() != config.numeroDePaginas) {
        cout << "Aviso: La tabla tiene " << config.tablaPaginas.size() << " entradas pero hay " << config.numeroDePaginas << " paginas." << "\n";
    }

    return true;
}