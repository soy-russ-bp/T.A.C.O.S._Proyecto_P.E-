#include "Orders.h"
#include "ConsoleColors.h"
#include "Exceptions.h"
#include "MathUtils.h"

// Total del día.
static double DayTotal;

// Total de ordenes que se han abierto.
static UINT TotalOrderCount;

// Cantidad de ordenes abiertas actualmente.
static UINT OpenOrderCount;

// Arreglo de las mesas.
static Table Tables[TableCount];

UINT Orders_GetOpenCount(void) {
	return OpenOrderCount;
}

Table* Orders_GetTableByIndex(size_t tableI) {
	AssertIsInArrayBounds(tableI, TableCount);
	return &Tables[tableI];
}

Table* Orders_GetTableByNum(size_t tableNum) {
	return Orders_GetTableByIndex(tableNum - 1);
}

bool Orders_IsValidTableNum(size_t tableNum) {
	return Math_IsInURange((UINT)tableNum, 1, TableCount);
}

bool Orders_IsTableOccupied(_In_ Table* table) {
	return table->id != 0;
}

double Orders_GetTableOrderTotal(_In_ Table* table) {
	double total = 0;
	LLOrderNode* node = LL_IterateStart;
	while (LLIterateFName(table->orderList, &node)) {
		OrderElement element = node->data;
		total += element.product->price * (double)element.count;
	}
	return total;
}

ConsoleStyle Orders_GetTableStatusColor(_In_ Table* table) {
	return Orders_IsTableOccupied(table) ? TableOccupiedColor : TableAvailableColor;
}

static void Orders_OpenTable(_Inout_ Table* table) {
	// TODO
	if (table->orderList == NULL) {
		table->orderList = LLOrder_New();
	}
	table->id = ++TotalOrderCount;
	OpenOrderCount++;
}

static void Orders_ClearTable(Table* table) {
	table->id = 0;
	LLOrder_Clear(table->orderList);
}

void Orders_CloseTable(_Inout_ Table* table) {
	Orders_ClearTable(table);
	DayTotal += Orders_GetTableOrderTotal(table);
}

void Orders_Cancel(_Inout_ Table* table) {
	Orders_ClearTable(table);
}

static const TSTR InvalidTableNumMsg = _T("# de mesa invalido");
static const TSTR OccupiedTableMsg = _T("Mesa ocupada");
static const TSTR NotOccupiedTableMsg = _T("Mesa no ocupada");

_Success_(OnFalseReturn) bool Orders_TryAssignTable(size_t tableNum, _Outptr_result_maybenull_z_ TSTR* errorMsg) {
	if (!Orders_IsValidTableNum(tableNum)) {
		*errorMsg = InvalidTableNumMsg;
		return false;
	}
	Table* table = Orders_GetTableByNum(tableNum);
	if (Orders_IsTableOccupied(table)) {
		*errorMsg = OccupiedTableMsg;
		return false;
	}
	Orders_OpenTable(table);
	return true;
}

_Success_(OnFalseReturn) bool Orders_IsValidAndOccupied(size_t tableNum, _Outptr_result_maybenull_z_ TSTR* errorMsg) {
	if (!Orders_IsValidTableNum(tableNum)) {
		*errorMsg = InvalidTableNumMsg;
		return false;
	}
	Table* table = Orders_GetTableByNum(tableNum);
	if (!Orders_IsTableOccupied(table)) {
		*errorMsg = NotOccupiedTableMsg;
		return false;
	}
	return true;
}
