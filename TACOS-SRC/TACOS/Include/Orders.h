#include "Flags.h"
#pragma once
#include "StringMap.h"
#include "ConsoleStyle.h"

#define TableCount 8
#define LastTableI (TableCount - 1)
#define TableOccupiedColor BACKGROUND_RED
#define TableAvailableColor BACKGROUND_GREEN

// Info de un producto del restaurante.
typedef struct {
	const TSTR name;
	const double price;
} Product;

// Elemento de una orden.
typedef struct {
	Product product;
	size_t count;
} OrderElement;

#define GDEF
#define GTYPE OrderElement
#define GNAME Order
#include "LinkedList.h"

// Información de una mesa.
typedef struct {
	UINT id;
	float moneySpent;
	LLOrder* orderList;
} Table;

// Obtiene la mesa en base a su indice.
Table* Orders_GetTableByIndex(size_t tableI);

// Obtiene la mesa en base a su número.
Table* Orders_GetTableByNum(size_t tableNum);

// Determina si tableNum es un número de mesa valido.
bool Orders_IsValidTableNum(size_t tableNum);

// Determina si la mesa esta ocupada.
bool Orders_IsTableOccupied(_In_ Table* table);

// Obtiene el color para una mesa en base a su disponibilidad.
ConsoleStyle Orders_GetTableStatusColor(_In_ Table* table);

// Trata de asignar una mesa, abriendo una nueva orden.
// La asignación será exitosa cuando tableNum sea un número de mesa valido y esta no este ocupada.
_Success_(OnFalseReturn) bool Orders_TryAssignTable(size_t tableNum, _Outptr_result_maybenull_z_ TSTR* errorMsg);

// Determina si el número de mesa se refiere a una ocupada.
_Success_(OnFalseReturn) bool Orders_IsValidAndOccupied(size_t tableNum, _Outptr_result_maybenull_z_ TSTR* errorMsg);
