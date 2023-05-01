#include "Flags.h"
#pragma once
#include <stdlib.h>
#include <malloc.h>
#include "StringMap.h"
#include "Exceptions.h"
#include "StrFormat.h"

// Asigna un espacio de la memoria dinámica con malloc.
// Si la asignación falla se finaliza la ejecución.
// A1 - void*     - out    - Variable en donde se guardara el ptr.
// A2 - allocSize - size_t - Tamaño de la asignación de memoria.
#define CheckedMalloc(out, allocSize) \
	out = malloc(allocSize); \
	Assert(out != NULL, "Error on malloc")

#define CheckedCopy(dst, src) \
	errno_t error = memcpy_s(&(dst), sizeof(dst), &(src), sizeof(src)); \
	Assert(!error, "Error executing memcpy_s")

#define GetAndStoreRawStrStackAlloc(charCount) _alloca( StrFormat_GetAllocSize(charCount) )

#if _DEBUG
#define RuntimeRawStrStackAlloc(charCount) StrFormat_FillAndNullTerminate(GetAndStoreRawStrStackAlloc(charCount), 'x', charCount)
#else
#define RuntimeRawStrStackAlloc(charCount) GetAndStoreRawStrStackAlloc(charCount)
#endif

#define RawStrStackAlloc(charCount) \
	WarnIgnore_Suppress(6255) \
	RuntimeRawStrStackAlloc( charCount )

#ifdef WidePrint
#define UnsafeMemSet wmemset
#define UnsafeMemCpy wmemcpy
#else
#define UnsafeMemSet memset
#define UnsafeMemCpy memccpy
#endif
