#include "Flags.h"
#pragma once

// Tipo de funci�n sin retorno y sin argumentos.
typedef void(*Action)(void);

// Ejecuta una funci�n de tipo action si no es NULL.
void Action_TryExecute(Action action);
