#include "Flags.h"
#pragma once
// M�dulo: StringMap
// Mapeo a los tipos y funciones correspondientes a las cadenas (un solo byte o multibyte).

#include <tchar.h>

// - Tipos - //
#ifdef WidePrint
typedef wint_t TCHINT;
#else
typedef int TCHINT;
#endif
typedef TCHAR* TSTR;

// - Funciones - //
#define TStrLen _tcslen
