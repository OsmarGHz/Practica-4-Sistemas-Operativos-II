#include "traduccion.h"
#include <bitset>
#include <sstream>
#include <iomanip>

using namespace std;

Traduccion traducirDireccion(const ConfiguracionMemoria & config,
                             const string & dirVirtualHexadecimal) {
    Traduccion t;
    t.direccionVirtualHexadecimal = dirVirtualHexadecimal;
    t.valida = true;

    int dirVirtual;

    try {
        dirVirtual = stoi(dirVirtualHexadecimal, nullptr, 16);
    } catch (...) {
        t.valida = false;
        t.mensajeError = "Direccion hexadecimal invalida";
        return t;
    }

    // Extraemos offset y numero de pagina
    t.offset = dirVirtual & ((1 << config.bitsOffset) - 1);
    t.numPagina = dirVirtual >> config.bitsOffset;

    // Validamos rango de pagina
    if (t.numPagina < 0 || t.numPagina >= config.numeroDePaginas) {
        t.valida = false;
        t.mensajeError = "Numero de pagina fuera de rango";
        return t;
    }

    // Obtenemos la entrada de la tabla
    int entrada = config.tablaPaginas[t.numPagina];

    // Extraemos marco (bits menos significativos)
    t.numMarco = entrada & ((1 << config.bitsMarco) - 1);

    // Extraemos los bits de control (los siguientes 5 bits)
    int bitsControl = entrada >> config.bitsMarco;

    t.bitPresente  =  bitsControl        & 1; //Presente ausente

    if (!t.bitPresente) {
        t.valida = false;
        t.mensajeError = "PAGE FAULT: la pagina no esta presente en memoria";
        return t;
    }

    t.bitCache     = (bitsControl >> 4) & 1;
    t.bitReferida  = (bitsControl >> 3) & 1;
    t.bitModificada= (bitsControl >> 2) & 1;
    t.bitProteccion= (bitsControl >> 1) & 1;

    // Construimos direccion fisica
    t.direccionFisica = (t.numMarco << config.bitsOffset) | t.offset;

    // Conversiones
    t.direccionFisicaBinario =
        aBinario(t.direccionFisica,
                 config.bitsMarco + config.bitsOffset);

    t.direccionFisicaHexadecimal =
        aHexadecimal(t.direccionFisica);

    return t;
}

string aBinario(int numero, int totalBits) {
    string resultado;
    for (int i = totalBits - 1; i >= 0; i--) {
        resultado += ((numero >> i) & 1) ? '1' : '0';
    }
    return resultado;
}

string aHexadecimal(int numero) {
    stringstream ss;
    ss << uppercase << hex << numero;
    return ss.str();
}

Traduccion desempaquetarEntrada(const ConfiguracionMemoria & config, int numPagina) {
    Traduccion t;
    t.numPagina = numPagina;
    int entrada = config.tablaPaginas[numPagina];
    t.numMarco = entrada & ((1 << config.bitsMarco) - 1);
    int bitsControl = entrada >> config.bitsMarco;
    t.bitCache      = (bitsControl >> 4) & 1;
    t.bitReferida   = (bitsControl >> 3) & 1;
    t.bitModificada = (bitsControl >> 2) & 1;
    t.bitProteccion = (bitsControl >> 1) & 1;
    t.bitPresente   =  bitsControl       & 1;
    t.valida = t.bitPresente;
    return t;
}