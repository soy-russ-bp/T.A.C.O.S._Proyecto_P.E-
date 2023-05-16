#include "Flags.h"
#pragma once
#include <wincontypes.h>

// Obtiene la posici�n actual del cursor de la consola.
COORD ConsoleCursor_GetPos(void);

// Establece la posici�n actual del cursor de la consola.
void ConsoleCursor_SetPos(COORD pos);

// Establece la posici�n actual del cursor de la consola.
void ConsoleCursor_SetPos2(SHORT x, SHORT y);

// Mueve el cursor horizontalmente desde su posici�n actual.
void ConsoleCursor_MoveX(SHORT xOffset);

// Establece la posici�n actual del cursor de la consola en (0,0).
void ConsoleCursor_ResetPos(void);
