﻿#include "MainMenu.h"
#include "Sleep.h"
#include "ArrayUtils.h"
#include "WarnIgnore.h"
#include "ConsoleOut.h"
#include "Orders.h"
#include "Options.h"
#include "NewOrder.h"
#include "ModifyOrder.h"
#include "CloseOrder.h"
#include "DaySummary.h"
#include "SystemEnd.h"

static const TSTR MainMenuOptionsList[] = { _T("Nueva orden"), _T("Modificar orden"), _T("Finalizar orden") };
static const OptionGroup MainMenuOptions = { StaticArrayAndLength(MainMenuOptionsList), OTExit };
static const TSTR OrderSeparatorRow = _T("╠═════════╬═════════╬══════════════════════════════════════╣╳║                           ║");
static const TSTR OrderEndrRow      = _T("╠═════════╩═════════╩══════════════════════════════════════╩═╩═══════════════════════════╣");

static TSTR GetSeparator(size_t orderI) {
	return (orderI == LastTableI) ? OrderEndrRow : OrderSeparatorRow;
}

static void PrintOrderInfo(size_t orderI) {
	int rowNum = (int)orderI + 1;
	ConsoleOut_WriteFormat(_T("║    %d    ║"), rowNum);
	Table* table = Orders_GetTableByIndex(orderI);
	if (Orders_IsTableOccupied(table)) {
		ConsoleOut_WriteAlignedUInt(table->id, 9, ALIGN_CENTER);
		double totalSpent = Orders_GetTableOrderTotal(table);
		size_t totalItems = Orders_GetTableOrderTotalItems(table);
		ConsoleOut_WriteFormat(_T("║  Cons: $%s  /  Cant art: %s  ║╳║%s║\n"),
			SF_AlignF(9, ALIGN_LEFT, _T("%.2f"), totalSpent),
			SF_AlignF(3, ALIGN_LEFT, _T("%d"), totalItems),
			SF_Repeat(' ', 27)
		);
	} else {
		ConsoleOut_WriteLine(_T("▒▒▒▒▒▒▒▒▒║▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒║╳║                           ║"));
	}
	ConsoleOut_WriteLine(GetSeparator(orderI));
}

static void PrintOrders(void) {
	for (size_t rowI = 0; rowI < TableCount; rowI++) {
		PrintOrderInfo(rowI);
	}
}

static void PrintMainMenuHeader(void) {
	ConsoleOut_WriteLine(_T("╔═════════╦═════════╦══════════════════════════════════════╦═╦═══════════════════════════╗"));
	ConsoleOut_WriteLine(_T("║   Mesa  ║  Orden  ║              Información             ║╳║          Opciones         ║"));
	ConsoleOut_WriteLine(_T("╠═════════╬═════════╬══════════════════════════════════════╣╳╠═══════════════════════════╣"));
}

static void PrintMainMenu(void) {
	PrintMainMenuHeader();
	PrintOrders();
	DaySummary_PrintTable();
}

static bool MainMenuOptionHandler(OptionHandlerArgs) {
	WarnIgnore_UnusedVar(extraInfo);
	TCHAR option = optionInput.single;
	switch (option) {
		case 'N':
			*navAction = &NewOrder_Menu;
			return true;
		case 'M': case 'F':
			if (Orders_GetOpenCount() == 0) {
				*errorMsg = _T("No hay mesas abiertas");
				return false;
			}
			*navAction = (option == 'M') ? &ModifyOrder_Menu : &CloseOrder_Menu;
			return true;
		case 'S':
			SystemEnd();
	}
	return false;
}

_Noreturn void MainMenu(void) {
	do {
		PrintMainMenu();
		HandleOptions(&MainMenuOptions, MainMenuOptionHandler);
		ConsoleOut_NewLineRepeat(2);
	} while (true);
}
