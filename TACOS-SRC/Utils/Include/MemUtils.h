#include "Flags.h"
#pragma once
#include <stdlib.h>
#include "Exceptions.h"

// Asigna un espacio de la memoria din�mica con malloc.
// Si la asignaci�n falla se finaliza la ejecuci�n.
// A1 - void*     - out    - Variable en donde se guardara el ptr.
// A2 - allocSize - size_t - Tama�o de la asignaci�n de memoria.
#define CheckedMalloc(out, allocSize) \
	out = malloc(allocSize); \
	Assert(out != NULL, "Error on malloc.")

#define CheckedCopy(dst, src) \
	errno_t error = memcpy_s(&(dst), sizeof(dst), &(src), sizeof(src)); \
	Assert(!error, "Error executing memcpy_s.")
