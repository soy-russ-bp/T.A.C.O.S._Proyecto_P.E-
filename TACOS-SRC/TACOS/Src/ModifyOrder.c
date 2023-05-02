#include "ModifyOrder.h"
#include "ConsoleOut.h"
#include "ConsoleCursor.h"
#include "ArrayUtils.h"
#include "TableSelection.h"
#include "Options.h"
#include "Orders.h"
#include "Products.h"

static const TSTR ModifyOrderOptionsList[] = { _T("Añadir producto"), _T("Eliminar producto") };
static const OptionGroup ModifyOrderOptions = { StaticArrayAndLength(ModifyOrderOptionsList), OTReturn };

#define ProductCellWidth (18)
#define RepBar(count) SF_Repeat(L'═', count)
#define FooterSeparatorRowI (18)

static void GetSeparatorChars(SHORT rowI, _Out_ TCHAR* middleCh, _Out_ TCHAR* endCh, _Outptr_ TSTR* wideVertSeparator) {
	if (rowI != FooterSeparatorRowI) {
		*middleCh = (rowI == 2) ? L'╦' : L'╬';
		*endCh = L'╣';
		*wideVertSeparator = _T("╣╳╳╠");
		return;
	}
	*middleCh = *endCh = L'╩';
	*wideVertSeparator = _T("╩══╩");
}

static void PrintHorizontalSeparator(SHORT rowI) {
	if (rowI == 0) {
		ConsoleCursor_SetPos2(1, rowI);
		ConsoleOut_WriteFormat(_T("%s╦══╦%s"), RepBar(30), RepBar(24));
		return;
	}
	ConsoleCursor_SetPos2(0, rowI);
	TCHAR middleCh, endCh;
	TSTR wideVertSeparator;
	GetSeparatorChars(rowI, &middleCh, &endCh, &wideVertSeparator);
	ConsoleOut_WriteFormat(_T("╠%s%c%s%c%s%s%s%c%s%c"),
		RepBar(5), middleCh, RepBar(ProductCellWidth), middleCh, RepBar(5),
		wideVertSeparator, RepBar(ProductCellWidth), middleCh, RepBar(5), endCh
	);
}

static void PrintMenuHeader(int tableNum, double total) {
	PrintHorizontalSeparator(0);
	ConsoleCursor_SetPos2(1, 1);
	ConsoleOut_WriteFormat(_T("%s║╳╳║ Mesa #%d Total: %.2f"),
		SF_Align(_T("Menú"), 30, ALIGN_CENTER), tableNum, total
	);
	PrintHorizontalSeparator(2);
	ConsoleCursor_SetPos2(1, 3);
	TSTR proHeaderTitle = SF_Align(_T("Producto"), ProductCellWidth, ALIGN_CENTER);
	ConsoleOut_WriteFormat(_T(" COD ║%s║ $$$ ║╳╳║%s║Cant."), proHeaderTitle, proHeaderTitle);
}

static void PrintMenuRow(size_t productI, SHORT rowI) {
	ConsoleCursor_SetPos2(0, rowI);
	ProductInfo product = Products_GetProductInfo(productI);
	ConsoleOut_WriteFormat(_T("║ %s ║%s║%.2f║"),
		product.code,
		SF_Align(product.name, ProductCellWidth, ALIGN_CENTER),
		product.price
	);
}
static void PrintListRow(LLOrder* orderList, size_t productI) {
	if (!Array_IsInBounds(productI, orderList->count)) {
		ConsoleOut_WriteFormat(_T("%s║%s"), SF_Repeat(L'▒', 18), SF_Repeat(L'▒', 5));
		return;
	}
}

static void PrintProductRow(Table* table, size_t productI, SHORT rowI) {
	PrintMenuRow(productI, rowI);
	ConsoleOut_Write(_T("╳╳║"));
	PrintListRow(table->orderList, productI);
}

static void PrintModifyOrderMenu(int tableNum, Table* table) {
	PrintMenuHeader(tableNum, table->moneySpent);
	SHORT printRowI = 4;
	for (size_t productI = 0; productI < Products_TypesCount; productI++) {
		PrintHorizontalSeparator(printRowI++);
		PrintProductRow(table, productI, printRowI++);
	}
	PrintHorizontalSeparator(FooterSeparatorRowI);
}

static bool ModifyOrderOptionHandler(OptionHandlerArgs) {
	WarnIgnore_UnusedVar(navAction);
	WarnIgnore_UnusedVar(errorMsg);
	WarnIgnore_UnusedVar(extraInfo);
	TCHAR option = optionInput.single;
	if (option == 'R') {
		return true;
	}
	return false;
}

void ModifyOrder_Menu(void) {
	int selectedTable = TableSelection_Menu(true);
	if (selectedTable == 0) return;
	Table* table = Orders_GetTableByNum((size_t)selectedTable);
	PrintModifyOrderMenu(selectedTable, table);
	HandleOptions(&ModifyOrderOptions, ModifyOrderOptionHandler);
}
