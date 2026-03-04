#include <iostream>
#include <locale>
#include <string>
#include "tipos.h"
#include "archivo.h"
#include "menu.h"

using namespace std;

int main(){
    ConfiguracionMemoria config;
    string nombreArchivo;
    cout << "=== Traductor de Direcciones Virtuales a Fisicas ===" << "\n";
    cout << "Ingrese el nombre del archivo de configuracion: ";
    cin >> nombreArchivo;

    if (!leerArchivo(nombreArchivo, config)) {
        cout << "Lo sentimos, no se pudo leer el archivo. Terminando..." << endl;
        return 1;
    }

    mostrarConfiguracion(config);
    mostrarExtra(config);
    ejecutarMenu(config);

    return 0;
}