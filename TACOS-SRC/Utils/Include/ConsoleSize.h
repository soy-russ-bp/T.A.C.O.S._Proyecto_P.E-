#include "Flags.h"
#pragma once

// Inicializa el m�dulo, llamar antes de usarlo.
void ConsoleSize_Init(void);

// Inhabilita la posibilidad de alterar el tama�o de la consola por el usuario.
void ConsoleSize_DisableResize(void);

// Establece el tama�o de la consola.
void ConsoleSize_Set(short width, short height);

// Establece el tama�o de la consola y lo bloquea en este.
void ConsoleSize_SetAndLock(short width, short height);
