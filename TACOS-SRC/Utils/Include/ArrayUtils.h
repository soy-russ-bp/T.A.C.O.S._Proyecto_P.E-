#include "Flags.h"
#pragma once

// Determina si un �ndice est� dentro del rango de un arreglo.
bool Array_IsInBounds(size_t index, size_t size);

// Longitud de un arreglo.
// El arreglo debe ser est�tico.
#define StaticLength(arr) (sizeof(arr)/sizeof(arr[0]))

// Arreglo seguido de su tama�o, en forma de lista de argumentos.
// El arreglo debe ser est�tico.
#define StaticArrayAndLength(arr) arr, StaticLength(arr)
