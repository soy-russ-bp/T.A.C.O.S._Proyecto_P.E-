#include "Flags.h"
// Módulo: LinkedList.c
// Implementación generica de lista enlazada
// Definir GTYPE y GNAME para crear una variante de un tipo en concreto

//#define LinkedListTest

#ifdef LinkedListTest

#undef GDEF
#undef GTYPE
#undef GNAME
#define GDEF
#define GTYPE int
#define GNAME Int
#define LinkedListTesting

#endif

#ifndef LinkedListTested

#ifdef GDEF

#ifndef GTYPE
#error Define GTYPE
#endif

#ifndef GNAME
#error Define GNAME
#endif

#include "MacroUtils.h"
#include "AllocUtils.h"

#define LLName TCONCAT(LL, GNAME)
#define LLPrefix TCONCAT(LLName, _)
#define AddLLPrefix(Name) TCONCAT(LLPrefix, Name)

#define P_LLPrefix TCONCAT(P_, LLPrefix)
#define AddP_LLPrefix(Name) TCONCAT(P_LLPrefix, Name)

// - Uso interno - //
#define LLNodeName TCONCAT(LLName, Node)
#define LLAllocNodeFName AddP_LLPrefix(AllocNode)
#define LLCreateNodeFName AddP_LLPrefix(CreateNode)
#define LLUpdateTailFName AddP_LLPrefix(UpdateTail)

// - Uso público - //
#define LLIterateFName AddLLPrefix(Iterate)
#define LLNewFName AddLLPrefix(New)
#define LLDeleteFName AddLLPrefix(Delete)
#define LLClearFName AddLLPrefix(Clear)
#define LLPrependFName AddLLPrefix(Prepend)
#define LLAppendFName AddLLPrefix(Append)
#define LLGetNodeAtFName AddLLPrefix(GetNodeAt)
#define LLRemoveNodeFName AddLLPrefix(RemoveNode)
#define LLRemoveAtFName AddLLPrefix(RemoveAt)
#define LLCwRotateFName AddLLPrefix(CwRotate)

#pragma warning( disable : 4820 )
// Nodo de una lista enlazada.
// M1 - GTYPE  - data - Datos del elemento.
// M2 - LL{GTYPE}Node - next - Siguiente elemento de la lista.
typedef struct LLNodeName {
	GTYPE data;
	struct LLNodeName* next;
	struct LLNodeName* last;
} LLNodeName;
#pragma warning( default : 4820 ) 

// Lista enlazada.
// No modificar directamente, usar los metodos de tipo LL_FUNC.
// Para crear una nueva instancia usar LL_New.
// M1 - LL_Node - head  - Primer elemento de la lista.
// M2 - LL_Node - tail  - Ultimo elemento de la lista.
// M3 - size_t  - count - Cantidad de elementos en la lista.
typedef struct {
	size_t count;
	LLNodeName* head;
	LLNodeName* tail;
} LLName;

// Uso interno. Asigna memoria a un nodo.
LLNodeName* LLAllocNodeFName(GTYPE data);

// Uso interno. Crea un nodo.
LLNodeName* LLCreateNodeFName(_In_ LLName* list, GTYPE data, _Out_ bool* furtherProcessRequired);

// Uso interno. Estable la nueva cola de la lista.
void LLUpdateTailFName(_In_ LLName* list, LLNodeName* newTail);

// Crea un contenedor de lista enlazada.
LLName* LLNewFName(void);

// Elimina un contenedor de lista enlazada y todos sus elementos.
void LLDeleteFName(_In_ LLName* list);

// Elimina todos los elementos de una lista enlazada.
void LLClearFName(_In_ LLName* list);

// Itera sobre una lista.
bool LLIterateFName(_In_ LLName* list, _Inout_ LLNodeName** currentNode);

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

LLNodeName* LLAllocNodeFName(GTYPE data) {
	LLNodeName* newNode;
	CheckedMalloc(newNode, sizeof(LLNodeName));
	memcpy(&newNode->data, &data, sizeof(GTYPE));
	newNode->next = NULL;
	newNode->last = NULL;
	return newNode;
}

LLNodeName* LLCreateNodeFName(_In_ LLName* list, GTYPE data, _Out_ bool* furtherProcessRequired) {
	LLNodeName* newNode = LLAllocNodeFName(data);
	*furtherProcessRequired = (list->head != NULL);
	if (!(*furtherProcessRequired)) {
		list->head = newNode;
		list->tail = newNode;
	}
	list->count++;
	return newNode;
}

void LLUpdateTailFName(_In_ LLName* list, LLNodeName* newTail) {
	list->tail->next = newTail;
	newTail->last = list->tail;
	list->tail = newTail;
}

LLName* LLNewFName(void) {
	LLName* head;
	CheckedMalloc(head, sizeof(LLName));
	*head = (LLName){ 0, NULL, NULL };
	return head;
}

void LLDeleteFName(_In_ LLName* list) {
	LLClearFName(list);
	free(list);
}

void LLClearFName(_In_ LLName* list) {
	LLNodeName* node = list->head;
	while (LLIterateFName(list, &node)) {
		free(node->last);
	}
	free(list->tail);
	list->head = NULL;
	list->tail = NULL;
	list->count = 0;
}

bool LLIterateFName(_In_ LLName* list, _Inout_ LLNodeName** currentNode) {
	*currentNode = (*currentNode == NULL) ? list->head : (*currentNode)->next;
	return (*currentNode != NULL);
}

void LLPrependFName(_In_ LLName* list, GTYPE data) {
	bool furtherProcessRequired;
	LLNodeName* newNode = LLCreateNodeFName(list, data, &furtherProcessRequired);
	if (!furtherProcessRequired) return;
	newNode->next = list->head;
	list->head->last = newNode;
	list->head = newNode;
}

void LLAppendFName(_In_ LLName* list, GTYPE data) {
	bool furtherProcessRequired;
	LLNodeName* newNode = LLCreateNodeFName(list, data, &furtherProcessRequired);
	if (!furtherProcessRequired) return;
	LLUpdateTailFName(list, newNode);
}

LLNodeName* LLGetNodeAtFName(_In_ LLName* list, size_t index) {
	LLNodeName* node = NULL;
	for (size_t nodeI = 0; nodeI <= index; nodeI++) {
		if (!LLIterateFName(list, &node)) {
			Throw("Index out of bounds of the list.");
		}
	}
	return node;
}

void LLRemoveNodeFName(_In_ LLName* list, _In_ LLNodeName* node) {
	if (node->last != NULL) {
		node->last->next = node->next;
	} else {
		list->head = node->next;
	}
	if (node->next != NULL) {
		node->next->last = node->last;
	} else {
		list->tail = node->last;
	}
	list->count--;
	free(node);
}

void LLRemoveAtFName(_In_ LLName* list, size_t index) {
	LLNodeName* node = LLGetNodeAtFName(list, index);
	LLRemoveNodeFName(list, node);
}

void LLCwRotateFName(_In_ LLName* list) {
	if (list->count < 2) return;

	LLNodeName* newTail = list->tail->last;
	newTail->next = NULL;

	LLNodeName* newHead = list->tail;
	newHead->next = list->head;
	newHead->last = NULL;
	list->head->last = newHead;

	list->head = newHead;
	list->tail = newTail;
}

#undef GDEF
#undef GTYPE
#undef GNAME

#ifdef LinkedListTesting
#define LinkedListTested
#endif


#endif

#endif
