#include "Flags.h"
#pragma once

// Determina si num esta en el rango [min, max].
// Todos los argumentos deben ser positivos.
bool Math_IsInURange(UINT num, UINT min, UINT max);

// Determina si num es par.
bool Math_IsEven(int num);

// Determina la cantidad de digitos de num.
size_t Math_DigitCount(int num);

// Segundos a milisegundos.
#define Math_SecToMs(seg) ((int)((seg) * 1000))

// Infinito
#define Infinite 0xFFFFFFFF
