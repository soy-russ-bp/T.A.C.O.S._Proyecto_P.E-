#include "Flags.h"
#pragma once
#include <wincontypes.h>

// Obtiene la posición actual del cursor de la consola.
COORD ConsoleCursor_GetPos(void);

// Establece la posición actual del cursor de la consola.
void ConsoleCursor_SetPos(COORD pos);

// Establece la posición actual del cursor de la consola.
void ConsoleCursor_SetPos2(SHORT x, SHORT y);

// Mueve el cursor horizontalmente desde su posición actual.
void ConsoleCursor_MoveX(SHORT xOffset);

// Establece la posición actual del cursor de la consola en (0,0).
void ConsoleCursor_ResetPos(void);
