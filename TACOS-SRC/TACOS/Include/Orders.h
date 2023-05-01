#include "Flags.h"
#pragma once
#include "StringMap.h"
#include "ConsoleStyle.h"
#include "OrderList.h"
#include "WarnIgnore.h"

#define TableCount 8
#define LastTableI (TableCount - 1)
#define TableOccupiedColor BACKGROUND_RED
#define TableAvailableColor BACKGROUND_GREEN

WarnIgnore_AddedPadding_S
// Informaci�n de una mesa.
typedef struct Table {
	UINT id;
	double moneySpent;
	LLOrder* orderList;
} Table;
WarnIgnore_AddedPadding_E

// Obtiene la cantidad de ordenes abiertas actualmente.
UINT Orders_GetOpenCount(void);

// Obtiene la mesa en base a su indice.
Table* Orders_GetTableByIndex(size_t tableI);

// Obtiene la mesa en base a su n�mero.
Table* Orders_GetTableByNum(size_t tableNum);

// Determina si tableNum es un n�mero de mesa valido.
bool Orders_IsValidTableNum(size_t tableNum);

// Determina si la mesa esta ocupada.
bool Orders_IsTableOccupied(_In_ Table* table);

// Obtiene el color para una mesa en base a su disponibilidad.
ConsoleStyle Orders_GetTableStatusColor(_In_ Table* table);

// Cierra una mesa.
void Orders_CloseTable(_Inout_ Table* table);

// Trata de asignar una mesa, abriendo una nueva orden.
// La asignaci�n ser� exitosa cuando tableNum sea un n�mero de mesa valido y esta no este ocupada.
_Success_(OnFalseReturn) bool Orders_TryAssignTable(size_t tableNum, _Outptr_result_maybenull_z_ TSTR* errorMsg);

// Determina si el n�mero de mesa se refiere a una ocupada.
_Success_(OnFalseReturn) bool Orders_IsValidAndOccupied(size_t tableNum, _Outptr_result_maybenull_z_ TSTR* errorMsg);
