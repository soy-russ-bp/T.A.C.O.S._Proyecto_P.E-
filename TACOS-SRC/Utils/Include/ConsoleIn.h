#include "Flags.h"
#pragma once
#include "StringMap.h"

// Obtiene un car�cter de la consola sin imprimirlo, ignorando teclas extendidas.
TCHAR ConsoleIn_GetCharNoEcho(void);

// Retorna hasta que el car�cter sea presionado.
void ConsoleIn_WaitForChar(TCHAR ch);

// Retorna hasta que enter sea presionado.
void ConsoleIn_WaitForEnter(void);

// Tipo de funci�n para filtrar caracteres.
// La aceptaci�n del car�cterer dependera del resultado de la funci�n:
// Verdadero = Aceptado. | Falso = Rechazado.
// Se puede modificar el car�cter de entrada modificando {inputChPtr}.
typedef bool(*CharFilter)(TCHAR* inputChPtr);

// Obtiene un car�cterer modificable hasta una confirmaci�n con la tecla enter.
TCHAR GetSingleSubmitChar(CharFilter filter);
