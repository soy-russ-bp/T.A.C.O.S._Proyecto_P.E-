#include "Flags.h"
#pragma once
#include "StringMap.h"
#include "Action.h"

// Tipo de opción.
typedef enum OptionType {
	OTReturn,
	OTNone,
	OTExit,
	OTConfirmExit
} OptionType;

// Grupo de opciones.
typedef struct OptionGroup {
	const TSTR* options;
	const int optionCount;
	const OptionType optionType;
} OptionGroup;

// Input del usuario. Filtro: (0-9) (A-Z) (a-z).
// Puede ser un único carácter o una cadena.
typedef union OptionInput {
	TCHAR single;
	TSTR string;
} OptionInput;

// Argumentos de un OptionHandler.
// OptionInput - Acceder a {single} o {string} dependiendo si el input es multiple o no.
// NavAction   - Asignar para navegar a otro menú (opcional).
// ErrorMsg    - Asignar para mostrar un mensaje de error personalizado (opcional).
// ExtraInfo   - Comunicación input/output (opcional). Se debe hacer cast al ptr correspondiente para acceder.
#define OptionHandlerArgs \
	_In_ OptionInput optionInput, \
	SalExt_Ptr_InNull_OutMaybeNull_ Action* navAction, \
	SalExt_Ptr_InNull_OutMaybeNull_ TSTR* errorMsg, \
	_Inout_opt_ void* extraInfo

// Tipo de función para administrar el flujo de ejecución en base al input.
typedef bool(OptionHandler)(OptionHandlerArgs);

// Imprime un OptionGroup, obtiene input del usuario (1 cadena) y se lo envía al optionHandler.
// BufSize: Debe incluir el null terminator.
void HandleStrOptions(TSTR inputBuf, size_t bufSize, const OptionGroup* optionGroup, OptionHandler optionHandler);

// Imprime un OptionGroup, obtiene input del usuario (1 cadena) y se lo envía al optionHandler.
// BufSize: Debe incluir el null terminator.
// ExtraInfo: Comunicación input/output con el OptionHandler, el cual debe hacer cast al ptr correspondiente para acceder.
void HandleStrOptionsExtra(TSTR inputBuf, size_t bufSize, const OptionGroup* optionGroup, OptionHandler optionHandler, _Inout_opt_ void* extraInfo);

// Imprime un OptionGroup, obtiene input del usuario (1 carácter) y se lo envía al optionHandler.
void HandleOptions(const OptionGroup* optionGroup, OptionHandler optionHandler);

// Imprime un OptionGroup, obtiene input del usuario y se lo envía al optionHandler.
// ExtraInfo: Comunicación input/output con el OptionHandler, el cual debe hacer cast al ptr correspondiente para acceder.
void HandleOptionsExtra(const OptionGroup* optionGroup, OptionHandler optionHandler, _Inout_opt_ void* extraInfo);
