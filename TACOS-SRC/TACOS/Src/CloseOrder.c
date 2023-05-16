#include "TableSelection.h"
#include "Orders.h"
#include "CloseOrder.h"
#include "StringMap.h"
#include "ArrayUtils.h"
#include "ConsoleOut.h"
#include "ConsoleCursor.h"
#include "WarnIgnore.h"
#include "Options.h"

static const TSTR CloseOrderMenuOptionsList[] = { _T("Finalizar"), _T("Cancelar") };
static const OptionGroup CloseOrderOptions = { StaticArrayAndLength(CloseOrderMenuOptionsList), OTReturn };

static bool CloseOrderOptionHandler(OptionHandlerArgs) {
	WarnIgnore_UnusedVar(navAction);
	AssertNotNull(extraInfo);
	Table* table = (Table*)extraInfo;
	TCHAR option = optionInput.single;
	switch (option) {
		case 'F':
			Orders_CloseTable(table);
			return true;
		case 'C':
			Orders_Cancel(table);
			return true;
		case 'R':
			return true;
	}
	*errorMsg = _T("Opción invalida");
	return false;
}

static void FillBlankForTotalPanel(void) {
	ConsoleOut_WriteCharRepeat(' ', 25);
	ConsoleOut_WriteChar(L'║');
}

static void PrintHorizontalSeparator(SHORT row) {
	ConsoleCursor_SetPos2(0, row);
	TCHAR middleCorner;
	TCHAR lastLCorner;
	TCHAR lastFill;
	TCHAR lastRCorner;
	switch (row) {
		case 2:
			middleCorner = L'╦';
			lastLCorner = L'╦';
			lastFill = L'═';
			lastRCorner = L'╣';
			break;
		default:
			middleCorner = L'╬';
			lastLCorner = L'╣';
			lastFill = ' ';
			lastRCorner = L'║';
			break;
		case 18:
			middleCorner = L'╩';
			lastLCorner = L'╩';
			lastFill = L'═';
			lastRCorner = L'╩';
			break;
	}
	ConsoleOut_WriteFormat(_T("╠%s%c%s%c%s%c%s%c"),
		SF_Repeat(L'═', 18), middleCorner, SF_Repeat(L'═', 5), middleCorner, SF_Repeat(L'═', 7),
		lastLCorner, SF_Repeat(lastFill, 25), lastRCorner
	);
}

static void PrintProductRow(SHORT row, OrderElement orderElement) {
	ConsoleCursor_SetPos2(0, row);
	const ProductInfo* product = orderElement.product;
	if (orderElement.product != NULL) {
		ConsoleOut_WriteFormat(_T("║%s║%s║%s║"),
			SF_Align(product->name, 18, ALIGN_CENTER),
			SF_AlignF(5, ALIGN_CENTER, _T("%d"), orderElement.count),
			SF_AlignF(7, ALIGN_CENTER, _T("%.2f"), product->price)
		);
	} else {
		ConsoleOut_WriteFormat(_T("║%s║%s║%s║"),
			SF_Repeat(L'▒', 18),
			SF_Repeat(L'▒', 5),
			SF_Repeat(L'▒', 7)
		);
	}
	FillBlankForTotalPanel();
}

static void PrintBlankRows(size_t rowCount, SHORT rowI) {
	if (rowCount == 0) return;
	OrderElement noProduct = { NULL, 0 };
	for (size_t blankRowI = 0; blankRowI < rowCount; blankRowI++) {
		PrintHorizontalSeparator(rowI++);
		PrintProductRow(rowI++, noProduct);
	}
}

static void PrintProducts(LLOrder* orderList) {
	LLOrderNode* node = LL_IterateStart;
	SHORT rowI = 4;
	while (LLIterateFName(orderList, &node)) {
		PrintHorizontalSeparator(rowI++);
		PrintProductRow(rowI++, node->data);
	}
	size_t blankRowCount = Products_TypesCount - orderList->count;
	PrintBlankRows(blankRowCount, rowI);
}

static void PrintFieldHeaders(void) {
	ConsoleCursor_SetPos2(1, 3);
	ConsoleOut_WriteFormat(_T("%s║Cant.║%s║"),
		SF_Align(_T("Producto"), 18, ALIGN_CENTER),
		SF_Align(_T("$$$"), 7, ALIGN_CENTER)
	);
	FillBlankForTotalPanel();
}

static void PrintTotalProductTypeAmount(SHORT offsetX, SHORT offsetY, TSTR title, size_t amount) {
	ConsoleCursor_SetPos2(35 + offsetX, 8 + offsetY);
	ConsoleOut_WriteFormat(_T("%s: %d"), title, (int)amount);
}

static void GetTypesCountInOrder(_In_ LLOrder* orderList, _Out_ size_t* tacoCount, _Out_ size_t* drinkCount) {
	*tacoCount = 0;
	*drinkCount = 0;
	LLOrderNode* node = LL_IterateStart;
	while (LLIterateFName(orderList, &node)) {
		OrderElement element = node->data;
		size_t elementAmount = element.count;
		if (!element.product->isDrink) {
			*tacoCount += elementAmount;
		} else {
			*drinkCount += elementAmount;
		}
	}
}

static void PrinTotalProductTypes(LLOrder* orderList) {
	PrintTotalProductTypeAmount(0, 0, _T("Total de prods"), orderList->count);
	size_t tacoCount, drinkCount;
	GetTypesCountInOrder(orderList, &tacoCount, &drinkCount);
	PrintTotalProductTypeAmount(1, 1, _T("Tacos"), tacoCount);
	PrintTotalProductTypeAmount(1, 2, _T("Bebidas"), drinkCount);
}

static void PrintTotalPanel(Table* table) {
	double subtotal = Orders_GetTableOrderTotal(table);
	double tipAmount = Orders_GetTipAmount(subtotal);
	ConsoleCursor_SetPos2(35, 4);
	ConsoleOut_WriteFormat(_T("    Subtotal: %.2f"), subtotal);
	ConsoleCursor_SetPos2(35, 5);
	ConsoleOut_WriteFormat(_T("Propina (%%%d): %.2f"), TipPercentage, tipAmount);
	ConsoleCursor_SetPos2(35, 6);
	ConsoleOut_WriteFormat(_T("       Total: %.2f"), subtotal + tipAmount);
	PrinTotalProductTypes(table->orderList);
}

static void PrintCloseOrderMenu(Table* table) {
	ConsoleCursor_SetPos2(1, 1);
	ConsoleOut_Write(SF_Align(_T("Mesa #3"), 58, ALIGN_CENTER));
	PrintHorizontalSeparator(2);
	PrintFieldHeaders();
	PrintProducts(table->orderList);
	PrintHorizontalSeparator(18);
	PrintTotalPanel(table);
}

void CloseOrder_Menu(void) {
	int selectedTableNum = TableSelection_Menu(true);
	if (selectedTableNum == 0) return;
	Table* table = Orders_GetTableByNum((size_t)selectedTableNum);
	PrintCloseOrderMenu(table);
	HandleOptionsExtra(&CloseOrderOptions, CloseOrderOptionHandler, table);
}
