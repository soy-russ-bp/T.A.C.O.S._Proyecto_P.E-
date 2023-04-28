#include "Flags.h"
#pragma once
#ifndef WidePrint
#include <stdio.h>
#endif
#include "StringMap.h"
#include "ConsoleStyle.h"

// Imprime una cadena en la consola.
void ConsoleOut_Write(const TSTR str);

// Imprime una cadena en la consola y avanza el cursor a la siguiente linea.
void ConsoleOut_WriteLine(const TSTR str);

// Imprime una cadena en la consola con el estilo especificado.
void ConsoleOut_WriteStyled(const TSTR str, ConsoleStyle style);

// Imprime una cadena con formato en la consola.
#define ConsoleOut_WriteFormat(format, ...) \
	_tprintf(format, __VA_ARGS__)

// Imprime un carácter en la consola.
void ConsoleOut_WriteChar(TCHAR ch);

// Imprime un carácter en la consola la cantidad de veces indicada.
void ConsoleOut_WriteCharRepeat(TCHAR ch, size_t repeatCount);

// Imprime un carácter en la consola la cantidad de veces indicada y con el estilo especificado.
void ConsoleOut_WriteCharRepeatStyled(TCHAR ch, size_t repeatCount, ConsoleStyle style);

// Imprime un entero positivo en la consola.
void ConsoleOut_WriteUInt(UINT num);

// Imprime de manera centrada un entero positivo en la consola.
void ConsoleOut_WriteCenteredUInt(UINT num, size_t width);

// Nueva linea en la consola.
void ConsoleOut_NewLine(void);

// Nuevas lineas en la consola la cantidad de veces indicada.
void ConsoleOut_NewLineRepeat(size_t repeatCount);

// Simula la pulsación de retroceso.
void ConsoleOut_Backspace(void);

// Limpia la consola.
void ConsoleOut_Clear(void);
