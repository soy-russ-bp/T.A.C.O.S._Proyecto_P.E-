#include "Flags.h"
#pragma once
#include <consoleapi2.h>

extern HWND ConsoleWindow;
extern HANDLE ConsoleInHandle;
extern HANDLE ConsoleOutHandle;

// Inicializa el m�dulo y configura la impresi�n.
void ConsoleConfig_Setup(void);

// Desabilita la selecci�n de texto del usuario.
void ConsoleConfig_DisableTextSelect(void);

// Estructura que contiene informaci�n del buffer de la consola.
typedef CONSOLE_SCREEN_BUFFER_INFO ConsoleBufferInfo;

// Llena una estructura de tipo ConsoleBufferInfo con el estado actual de la consola.
void ConsoleConfig_FillConsoleBufferInfo(ConsoleBufferInfo* consoleBufferInfo);

// Obtiene un LongPtr de la ventana de la consola.
LONG_PTR ConsoleConfig_GetWindowLongPtr(int nIndex);

// Establece un LongPtr de la ventana de la consola.
void ConsoleConfig_SetWindowLongPtr(int nIndex, LONG_PTR newLongPtr);
