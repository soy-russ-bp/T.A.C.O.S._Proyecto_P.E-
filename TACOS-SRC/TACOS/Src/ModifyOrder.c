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

static const TSTR AddOrRemoveProductOptionsList[] = { _T("~#Código de producto"), _T("~#CCC (Cancelar)") };
static const OptionGroup AddOrRemoveProductOptions = { StaticArrayAndLength(AddOrRemoveProductOptionsList), OTReturn };

static const TSTR SelectAmountOptionsList[] = { _T("~#Cant. de producto"), _T("~#CCC (Cancelar)") };
static const OptionGroup SelectAmountOptions = { StaticArrayAndLength(SelectAmountOptionsList), OTReturn };

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
	const ProductInfo* product = Products_GetProductInfo(productI);
	ConsoleOut_WriteFormat(_T("║ %s ║%s║%.2f║"),
		product->code,
		SF_Align(product->name, ProductCellWidth, ALIGN_CENTER),
		product->price
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

static void PrintListRow(_In_opt_ OrderElement* orderElement) {
	TSTR cellA;
	TSTR cellB;
	if (orderElement == NULL) {
		cellA = SF_Repeat(L'▒', 18);
		cellB = SF_Repeat(L'▒', 5);
	} else {
		cellA = SF_Align(orderElement->product->name, 18, ALIGN_CENTER);
		cellB = SF_AlignF(5, ALIGN_CENTER, _T("%d"), orderElement->count);
	}
	ConsoleOut_WriteFormat(_T("%s║%s"), cellA, cellB);
}

static void PrintProductRow(_In_opt_ OrderElement* orderElement, size_t productI, SHORT rowI) {
	PrintMenuRow(productI, rowI);
	ConsoleOut_Write(_T("╳╳║"));
	PrintListRow(orderElement);
}

static void PrintModifyOrderMenu(int tableNum, Table* table) {
	PrintMenuHeader(tableNum, Orders_GetTableOrderTotal(table));
	LLOrder* order = table->orderList;
	LLOrderNode* orderElement = NULL;
	bool orderEndReached = false;
	SHORT printRowI = 4;
	for (size_t productI = 0; productI < Products_TypesCount; productI++) {
		PrintHorizontalSeparator(printRowI++);
		orderEndReached = orderEndReached || !LLOrder_Iterate(order, &orderElement);
		OrderElement* orderElementData = (orderElement == NULL) ? NULL : &orderElement->data;
		PrintProductRow(orderElementData, productI, printRowI++);
		if (orderEndReached) orderElement = NULL;
	}
	PrintHorizontalSeparator(FooterSeparatorRowI);
}

static bool SelectOperationOptionHandler(OptionHandlerArgs) {
	WarnIgnore_UnusedVar(navAction);
	WarnIgnore_UnusedVar(errorMsg);
	TCHAR option = optionInput.single;
	switch (option) {
		case 'A': case 'E':
			AssertNotNull(extraInfo);
			ModOperation operation = (option == 'A') ? MOAdd : MORemove;
			*((ModOperation*)extraInfo) = operation;
			// TODO: MORemove: prod count 0 (LLOrder)
			return true;
		case 'R':
			return true;
	}
	return false;
}

static bool SearchForProduct(_In_ OrderElement* data, size_t index, _Inout_ void* extraInfo) {
	WarnIgnore_UnusedVar(index);
	const ProductInfo* menuProd = ((const ProductInfo*)extraInfo);
	return menuProd->code == data->product->code;
}

typedef struct {
	_In_ LLOrder* selectedOrder;
	_In_ LLOrderNode* selectedProductToRemove;
	_Out_ const ProductInfo* selectedMenuProduct;
} ModProductInfo;

static bool AddProductOptionHandler(OptionHandlerArgs) {
	WarnIgnore_UnusedVar(navAction);
	TSTR inputCode = optionInput.string;
	if (TStrCmp(inputCode, _T("CCC")) == 0) return true;
	size_t menuProdI;
	const ProductInfo* menuProd;
	if (Products_TryGetByCode(inputCode, &menuProdI, &menuProd)) {
		AssertNotNull(extraInfo);
		ModProductInfo* modProductInfo = ((ModProductInfo*)extraInfo);
		modProductInfo->selectedMenuProduct = menuProd;
		HighlightMenuRow(menuProdI);
		return true;
	}
	*errorMsg = _T("Código invalido");
	return false;
}

static bool RemoveProductOptionHandler(OptionHandlerArgs) {
	WarnIgnore_UnusedVar(navAction);

	AssertNotNull(extraInfo);
	ModProductInfo* modProductInfo = ((ModProductInfo*)extraInfo);
	LLOrder* selectedOrder = modProductInfo->selectedOrder;

	TSTR inputCode = optionInput.string;
	if (TStrCmp(inputCode, _T("CCC")) == 0) return true;

	size_t menuProdI;
	const ProductInfo* menuProd = modProductInfo->selectedMenuProduct;
	if (Products_TryGetByCode(inputCode, &menuProdI, &menuProd)) {
		void* menuProdAsInfo = WarnIgnore_CastDropQualifiers((void*)menuProd);
		LLOrderNode* orderElement;
		if (LLOrder_TryFind(selectedOrder, SearchForProduct, menuProdAsInfo, NULL, &orderElement)) {
			//HighlightMenuRow(menuProdI);
			modProductInfo->selectedProductToRemove = orderElement;
			return true;
		}
		*errorMsg = _T("El producto debe estar en la orden");
		return false;
	}
	*errorMsg = _T("Código invalido");
	return false;
	
}

static bool SelectAddAmountOptionHandler(OptionHandlerArgs) {
	WarnIgnore_UnusedVar(navAction);
	AssertNotNull(extraInfo);
	ModProductInfo* modProductInfo = ((ModProductInfo*)extraInfo);
	LLOrder* selectedOrder = modProductInfo->selectedOrder;

	TSTR inputAmount = optionInput.string;
	size_t amount = _tcstol(inputAmount, NULL, 10);

	const ProductInfo* menuProd = modProductInfo->selectedMenuProduct;
	void* menuProdAsInfo = WarnIgnore_CastDropQualifiers((void*)menuProd);

	size_t amountTotal = amount;
	LLOrderNode* orderElement = NULL;
	if ((selectedOrder->count) > 0) {
		LLOrder_TryFind(selectedOrder, SearchForProduct, menuProdAsInfo, NULL, &orderElement);
		amountTotal += orderElement->data.count;
	}
	if (amount == 0) {
		*errorMsg = _T("Cantidad invalida");
		return false;
	}
	if (amountTotal > 25) {
		*errorMsg = _T("Máx: 25");
		return false;
	}
	if (orderElement != NULL) {
		orderElement->data.count += amount;
	} else {
		OrderElement newOrderElement = { menuProd, amount };
		LLOrder_Append(selectedOrder, newOrderElement);
	}
	return true;
}

static bool SelectRemoveAmountOptionHandler(OptionHandlerArgs) {
	WarnIgnore_UnusedVar(navAction);
	AssertNotNull(extraInfo);
	ModProductInfo* modProductInfo = ((ModProductInfo*)extraInfo);
	//LLOrder* selectedOrder = modProductInfo->selectedOrder;

	TSTR inputAmount = optionInput.string;
	int amount = _tcstol(inputAmount, NULL, 10);

	LLOrderNode* prodToRemove = modProductInfo->selectedProductToRemove;
	if ((int)prodToRemove->data.count - amount < 0) {
		*errorMsg = _T("No se puede remover más productos de los que hay.");
		return false;
	}
	return true;
}

static void GetContextOptionHandlers(ModOperation modOperation, OptionHandler** operationOptionHandler, OptionHandler** selectAmountOptionHandler) {
	if (modOperation == MOAdd) {
		*operationOptionHandler = AddProductOptionHandler;
		*selectAmountOptionHandler = SelectAddAmountOptionHandler;
	} else {
		*operationOptionHandler = RemoveProductOptionHandler;
		*selectAmountOptionHandler = SelectRemoveAmountOptionHandler;
	}
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
			case MOAdd: case MORemove:
				TCHAR inputBuf[ProductCodeBufSize];
				ModProductInfo selectedMenuProduct = {0};
				selectedMenuProduct.selectedOrder = table->orderList;
				OptionHandler* operationOptionHandler;
				OptionHandler* selectAmountOptionHandler;
				GetContextOptionHandlers(modOperation, &operationOptionHandler, &selectAmountOptionHandler);
				HandleStrOptionsExtra(StaticArrayAndLength(inputBuf), &AddOrRemoveProductOptions, operationOptionHandler, &selectedMenuProduct);
				HandleStrOptionsExtra(inputBuf, (size_t)(2 + 1), &SelectAmountOptions, selectAmountOptionHandler, &selectedMenuProduct);
				break;
			default:
				Throw("Invalid mod operation");
		}
	} while (true);
}
