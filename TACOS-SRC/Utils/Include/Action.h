#include "Flags.h"
#pragma once

// Tipo de función sin retorno y sin argumentos.
typedef void(*Action)(void);

// Ejecuta una función de tipo action si no es NULL.
void Action_TryExecute(Action action);
