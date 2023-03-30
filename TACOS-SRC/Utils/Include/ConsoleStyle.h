#include "Flags.h"
#pragma once
#include <minwindef.h>
#include "ConsoleColors.h"

// Tipo del estilo de la consola (color, subrayado, etc).
typedef WORD ConsoleStyle;

// Obtiene el estilo actual de la consola.
ConsoleStyle ConsoleStyle_Get(void);

// Establece el estilo actual de la consola.
void ConsoleStyle_Set(ConsoleStyle style);

// Reinicia el estilo de la consola.
void ConsoleStyle_Reset(void);
