#include "Flags.h"
#pragma once
#include "StringMap.h"

// Tipo de opción.
// TODO: Documentar tipos
typedef enum {
	OTReturn,
	OTExit,
	OTConfirmExit
} OptionType;

// Grupo de opciones.
typedef struct {
	const TSTR* options;
	const int optionCount;
	const OptionType optionType;
} OptionGroup;

// Tipo de función sin retorno y sin argumentos.
typedef void(*Action)(void);

// TODO
#define OptionHandlerArgs TCHAR option, Action* action, TSTR* errorMsg, void* extraInfo

// TODO
typedef bool(OptionHandler)(OptionHandlerArgs);

// TODO
void HandleOptions(const OptionGroup* optionGroup, OptionHandler optionHandler);

// TODO
void HandleOptionsExtra(const OptionGroup* optionGroup, OptionHandler optionHandler, _Inout_opt_ void* extraInfo);
