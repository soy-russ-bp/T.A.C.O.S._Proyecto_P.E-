#include "Flags.h"
#pragma once

// Inicializa el módulo, llamar antes de usarlo.
void ConsoleSize_Init(void);

// Inhabilita la posibilidad de alterar el tamaño de la consola por el usuario.
void ConsoleSize_DisableResize(void);

// Establece el tamaño de la consola.
void ConsoleSize_Set(short width, short height);

// Establece el tamaño de la consola y lo bloquea en este.
void ConsoleSize_SetAndLock(short width, short height);
