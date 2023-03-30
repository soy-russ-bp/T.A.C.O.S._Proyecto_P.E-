#include "Orders.h"
#include "ConsoleColors.h"
#include "Exceptions.h"
#include "MathUtils.h"

// Total de ordenes que se han abierto.
static UINT OrderCount;

// Arreglo de las mesas.
static Table Tables[TableCount];

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

ConsoleStyle Orders_GetTableStatusColor(_In_ Table* table) {
	return Orders_IsTableOccupied(table) ? TableOccupiedColor : TableAvailableColor;
}

bool Orders_TryAssignTable(size_t tableNum, _Outptr_result_maybenull_z_ TSTR* errorMsg) {
	if (!Orders_IsValidTableNum(tableNum)) {
		*errorMsg = _T("# de mesa invalido");
		return false;
	}
	Table* table = Orders_GetTableByNum(tableNum);
	if (Orders_IsTableOccupied(table)) {
		*errorMsg = _T("Mesa ocupada");
		return false;
	}
	*errorMsg = NULL;
	table->id = ++OrderCount;
	return true;
}
