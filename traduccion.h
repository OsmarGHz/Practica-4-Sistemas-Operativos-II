#ifndef TRADUCCION_H
#define TRADUCCION_H
#include <string>
#include "tipos.h"

using namespace std;
/*
Traduce una dirección virtual (en hexadecimal) a dirección física
Recibe la configuración de memoria y la dirección virtual como string hex
Retorna un struct Traduccion con todos los resultados
*/
Traduccion traducirDireccion(const ConfiguracionMemoria & config, const string & dirVirtualHexadecimal);

/*
Convierte un entero a su representación en binario como string
totalBits indica cuántos bits debe tener el resultado (con ceros a la izquierda)
*/
string aBinario(int numero, int totalBits); 

/*
Convierte un entero a su representación en hexadecimal como string
*/
string aHexadecimal(int numero);

#endif