#include "Flags.h"
#pragma once
#include <stdlib.h>
#include "Exceptions.h"

// Asigna un espacio de la memoria dinámica con malloc.
// Si la asignación falla se finaliza la ejecución.
// A1 - void*     - out    - Variable en donde se guardara el ptr.
// A2 - allocSize - size_t - Tamaño de la asignación de memoria.
#define CheckedMalloc(out, allocSize) \
	out = malloc(allocSize); \
	Assert(out != NULL, "Error on malloc.")

#define CheckedCopy(dst, src) \
	errno_t error = memcpy_s(&(dst), sizeof(dst), &(src), sizeof(src)); \
	Assert(!error, "Error executing memcpy_s.")
