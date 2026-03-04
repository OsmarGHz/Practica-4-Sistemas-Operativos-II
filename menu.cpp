#include "menu.h"
#include "traduccion.h"
#include <iostream>
#include <iomanip>

using namespace std;

void mostrarConfiguracion(const ConfiguracionMemoria & config) {
    cout << "\n=== Configuracion de Memoria ===\n";
    cout << "Tamano de pagina: " << config.tamanoPagina << " bytes\n";
    cout << "Tamano memoria virtual: " << config.tamanoMemoriaVirtual << " bytes\n";
    cout << "Tamano memoria fisica: " << config.tamanoMemoriaFisica << " bytes\n";
    cout << "Numero de paginas: " << config.numeroDePaginas << "\n";
    cout << "Numero de marcos: " << config.numeroDeMarcos << "\n";
    cout << "Bits de pagina: " << config.bitsPagina << "\n";
    cout << "Bits de marco: " << config.bitsMarco << "\n";
    cout << "Bits de offset: " << config.bitsOffset << "\n";
}

void mostrarExtra(const ConfiguracionMemoria & config){
    for (int i = 0; i < config.numeroDePaginas; i++) {
        int entrada = config.tablaPaginas[i];
        Traduccion t = desempaquetarEntrada(config, i);
        cout << setw(10) << i << " | " << setw(7) << entrada << " | ";
        if (t.bitPresente) {
            int bitsControl = entrada >> config.bitsMarco;
            cout << setw(20) << aBinario(bitsControl, 5) << "  | " << setw(10) << t.numMarco << "\n";
        } else {
            cout << setw(20) << " " << "  | " << "\n";
        }
    }

}

void mostrarTraduccion(const Traduccion & trad) {
    cout << "\n=== Resultado de la Traduccion ===\n";
    cout << "Direccion virtual (hex): " << trad.direccionVirtualHexadecimal << "\n";

    if (!trad.valida) {
        cout << "ERROR: " << trad.mensajeError << "\n";
        return;
    }

    cout << "Pagina virtual: " << trad.numPagina << "\n";
    cout << "Offset: " << trad.offset << "\n";

    cout << "\nBits de control:\n";
    cout << "Cache inhabilitada (C): " << trad.bitCache << "\n";
    cout << "Referida (R): " << trad.bitReferida << "\n";
    cout << "Modificada (M): " << trad.bitModificada << "\n";
    cout << "Proteccion (P): " << trad.bitProteccion << "\n";
    cout << "Presente (V): " << trad.bitPresente << "\n";

    cout << "\nMarco fisico: " << trad.numMarco << "\n";
    cout << "Direccion fisica (decimal): " << trad.direccionFisica << "\n";
    cout << "Direccion fisica (hex): " << trad.direccionFisicaHexadecimal << "\n";
    cout << "Direccion fisica (bin): " << trad.direccionFisicaBinario << "\n";
}

void ejecutarMenu(ConfiguracionMemoria & config) {
    string dirHex;

    while (true) {
        cout << "\nIngrese una direccion virtual en hexadecimal (o 'salir'): ";
        cin >> dirHex;

        if (dirHex == "salir") {
            cout << "Saliendo del programa...\n";
            break;
        }

        Traduccion resultado = traducirDireccion(config, dirHex);
        mostrarTraduccion(resultado);
    }
}
