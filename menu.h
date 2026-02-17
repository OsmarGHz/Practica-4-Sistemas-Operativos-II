#ifndef MENU_H
#define MENU_H

#include "tipos.h"

// Para mostrar la info de configuración de memoria
void mostrarConfiguracion(const ConfiguracionMemoria & config);

// Muestra el resultado de una traducción
void mostrarTraduccion(const Traduccion & trad);

void ejecutarMenu(ConfiguracionMemoria & config);

#endif