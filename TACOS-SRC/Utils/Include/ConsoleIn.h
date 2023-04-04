#include "Flags.h"
#pragma once
#include "StringMap.h"

// Obtiene un carácter de la consola sin imprimirlo, ignorando teclas extendidas.
TCHAR ConsoleIn_GetCharNoEcho(void);

// Retorna hasta que el carácter sea presionado.
void ConsoleIn_WaitForChar(TCHAR ch);

// Retorna hasta que enter sea presionado.
void ConsoleIn_WaitForEnter(void);

// Tipo de función para filtrar caracteres.
// La aceptación del carácterer dependera del resultado de la función:
// Verdadero = Aceptado. | Falso = Rechazado.
// Se puede modificar el carácter de entrada modificando {inputChPtr}.
typedef bool(*CharFilter)(TCHAR* inputChPtr);

// Obtiene un carácterer modificable hasta una confirmación con la tecla enter.
TCHAR GetSingleSubmitChar(CharFilter filter);
