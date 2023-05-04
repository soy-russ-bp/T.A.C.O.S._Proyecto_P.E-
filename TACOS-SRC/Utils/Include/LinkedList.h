#include "Flags.h"
// Módulo: LinkedList.h
// Implementación generica de lista enlazada.
// Definir GDEC or GDEF: GDEC en el .h y GDEF en el .c.
// Si se trata de GDEC: definir GTYPE y GNAME para generar una variante de un tipo en concreto.

#if defined(GDEF)

#define LinkedListIgnoreEdit

#pragma warning( disable : 4464 )
#include "../Src/LinkedList.c"
#pragma warning( default : 4464 )

#elif defined(GDEC)

#undef GDEC

#ifndef GTYPE
#error Define GTYPE
#endif

#ifndef GNAME
#error Define GNAME
#endif

#include "MacroUtils.h"
#include "WarnIgnore.h"

#define LLName TCONCAT(LL, GNAME)
#define LLPrefix TCONCAT(LLName, _)
#define AddLLPrefix(Name) TCONCAT(LLPrefix, Name)

#define LLNodeName TCONCAT(LLName, Node)
#define LLIterateFName AddLLPrefix(Iterate)
#define LLTryFindName AddLLPrefix(TryFind)
#define LLNewFName AddLLPrefix(New)
#define LLDeleteFName AddLLPrefix(Delete)
#define LLClearFName AddLLPrefix(Clear)
#define LLPrependFName AddLLPrefix(Prepend)
#define LLAppendFName AddLLPrefix(Append)
#define LLGetNodeAtFName AddLLPrefix(GetNodeAt)
#define LLRemoveNodeFName AddLLPrefix(RemoveNode)
#define LLRemoveAtFName AddLLPrefix(RemoveAt)
#define LLCwRotateFName AddLLPrefix(CwRotate)

WarnIgnore_AddedPadding_S
// Nodo de una lista enlazada.
// M1 - GTYPE  - data - Datos del elemento.
// M2 - LL{GTYPE}Node - next - Siguiente elemento de la lista.
typedef struct LLNodeName {
	GTYPE data;
	struct LLNodeName* next;
	struct LLNodeName* last;
} LLNodeName;
WarnIgnore_AddedPadding_E

// Lista enlazada.
// No modificar directamente, usar los metodos de tipo LL_FUNC.
// Para crear una nueva instancia usar LL_New.
// M1 - LL_Node - head  - Primer elemento de la lista.
// M2 - LL_Node - tail  - Ultimo elemento de la lista.
// M3 - size_t  - count - Cantidad de elementos en la lista.
typedef struct LLName {
	size_t count;
	LLNodeName* head;
	LLNodeName* tail;
} LLName;

// Crea un contenedor de lista enlazada.
LLName* LLNewFName(void);

// Elimina un contenedor de lista enlazada y todos sus elementos.
void LLDeleteFName(_In_ LLName* list);

// Elimina todos los elementos de una lista enlazada.
void LLClearFName(_In_ LLName* list);

// Itera sobre una lista.
bool LLIterateFName(_In_ LLName* list, _Inout_ LLNodeName** currentNode);

// Función de busqueda de un elemento.
typedef bool(*LLSearchPredicate)(_In_ GTYPE* data, size_t index, _Inout_ void* extraInfo);

// Busca entre los elementos de la lista.
_Success_(OnTrueReturn) bool LLTryFindName(_In_ LLName* list, LLSearchPredicate searchFunc, _Inout_ void* extraInfo, _Out_opt_ size_t* nodeIndex, _Out_opt_ LLNodeName** node);

// Añade un elemento al principio de la lista.
void LLPrependFName(_In_ LLName* list, GTYPE data);

// Añade un elemento al final de la lista.
void LLAppendFName(_In_ LLName* list, GTYPE data);

// Obtiene el elemento en el índice.
LLNodeName* LLGetNodeAtFName(_In_ LLName* list, size_t index);

// Remueve un elemento.
void LLRemoveNodeFName(_In_ LLName* list, _In_ LLNodeName* node);

// Remueve el elemento en el índice.
void LLRemoveAtFName(_In_ LLName* list, size_t index);

// Mueve el último elemento al principio de la lista.
void LLCwRotateFName(_In_ LLName* list);

#elif !defined(__clang_analyzer__)
#error Define GDEC or GDEF
#endif
