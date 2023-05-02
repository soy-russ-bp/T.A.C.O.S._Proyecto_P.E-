#include "ModifyOrder.h"
#include "ConsoleOut.h"
#include "ConsoleStyle.h"
#include "ConsoleCursor.h"
#include "ArrayUtils.h"
#include "TableSelection.h"
#include "Options.h"
#include "Orders.h"
#include "Products.h"

static const TSTR SelectOperationOptionsList[] = { _T("Añadir producto"), _T("Eliminar producto") };
static const OptionGroup SelectOperationOptions = { StaticArrayAndLength(SelectOperationOptionsList), OTReturn };
typedef enum ModOperation {
	MOAdd, MORemove, MOExit
} ModOperation;

static const TSTR AddProductOptionsList[] = { _T("~#Códdigo de producto"), _T("~#CCC   (Cancelar)") };
static const OptionGroup AddProductOptions = { StaticArrayAndLength(AddProductOptionsList), OTReturn };

#define ProductCodeLen (3)
#define ProductCodeBufSize (ProductCodeLen + 1)
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

static void HighlightMenuRow(size_t productI) {
	COORD oldCursorPos = ConsoleCursor_GetPos();
	ConsoleStyle oldStyle = ConsoleStyle_GetSet(BACKGROUND_GREEN | FOREGROUND_WHITE);
	SHORT rowI = (SHORT)(5 + (productI * 2));
	PrintMenuRow(productI, rowI);
	ConsoleCursor_SetPos(oldCursorPos);
	ConsoleStyle_Set(oldStyle);
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

static bool SelectOperationOptionHandler(OptionHandlerArgs) {
	WarnIgnore_UnusedVar(navAction);
	WarnIgnore_UnusedVar(errorMsg);
	TCHAR option = optionInput.single;
	switch (option) {
		case 'A': case 'E':
			ModOperation* modOp = ((ModOperation*)extraInfo);
			AssertNotNull(modOp);
			ModOperation operation = (option == 'A') ? MOAdd : MORemove;
			*modOp = operation;
			return true;
		case 'R':
			return true;
	}
	return false;
}

static bool AddProductOptionHandler(OptionHandlerArgs) {
	WarnIgnore_UnusedVar(navAction);
	WarnIgnore_UnusedVar(extraInfo);
	TSTR inputCode = optionInput.string;
	if (TStrCmp(inputCode, _T("CCC")) == 0) return true;
	size_t productI;
	if (Products_TryGetIndexByCode(inputCode, &productI)) {
		HighlightMenuRow(productI);
		return true;
	}
	*errorMsg = _T("Código invalido");
	return false;
}

void ModifyOrder_Menu(void) {
	int selectedTable = TableSelection_Menu(true);
	if (selectedTable == 0) return;
	Table* table = Orders_GetTableByNum((size_t)selectedTable);
	do {
		PrintModifyOrderMenu(selectedTable, table);
		ModOperation modOperation = MOExit;
		HandleOptionsExtra(&SelectOperationOptions, SelectOperationOptionHandler, &modOperation);
		switch (modOperation) {
			case MOExit:
				return; // TODO: Confirm changes (if any)
			case MOAdd:
				TCHAR code[ProductCodeBufSize];
				HandleStrOptions(StaticArrayAndLength(code), &AddProductOptions, AddProductOptionHandler);
				break;
			case MORemove:

				break;
			default:
				Throw("Invalid mod operation");
		}
	} while (true);
}
