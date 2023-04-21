#include "MainMenu.h"
#include "Sleep.h"
#include "ArrayUtils.h"
#include "ConsoleOut.h"
#include "Orders.h"
#include "Options.h"
#include "NewOrder.h"
#include "ModifyOrderP1.h"
#include "SystemEnd.h"
#include "MacroUtils.h"

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
		ConsoleOut_WriteCenteredUInt(table->id, 9);
		ConsoleOut_WriteLine(_T("║  Consumo: $0000.00  /  Cant art: 00  ║╳║                           ║"));
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

static void PrintMainMenu(void) {
	ConsoleOut_WriteLine(_T("╔═════════╦═════════╦══════════════════════════════════════╦═╦═══════════════════════════╗"));
	ConsoleOut_WriteLine(_T("║   Mesa  ║  Orden  ║              Información             ║╳║          Opciones         ║"));
	ConsoleOut_WriteLine(_T("╠═════════╬═════════╬══════════════════════════════════════╣╳╠═══════════════════════════╣"));
	PrintOrders();
	ConsoleOut_WriteLine(_T("╠════════════════════════════════════════════════════════════════════════════════════════╣"));
	ConsoleOut_WriteLine(_T("║                                     Resumen del día                                    ║"));
	ConsoleOut_WriteLine(_T("╠═══════════════════════════════════════════╦╦═══════════════════════════════════════════╣"));
	ConsoleOut_WriteLine(_T("║                  Ingresos                 ║║                  Ordenes                  ║"));
	ConsoleOut_WriteLine(_T("╠═══════════════════════════════════════════╣╠═══════════════════════════════════════════╣"));
	ConsoleOut_WriteLine(_T("║ Subtotal: $0                              ║║ Abiertas: 0                               ║"));
	ConsoleOut_WriteLine(_T("║  Propina: $0                              ║║ Cerradas: 0                               ║"));
	ConsoleOut_WriteLine(_T("║    Total: $0                              ║║  Totales: 0                               ║"));
	ConsoleOut_WriteLine(_T("╠═══════════════════════════════════════════╩╩═══════════════════════════════════════════╣"));
	ConsoleOut_WriteLine(_T("║ Opción:                                                                                ║"));
	ConsoleOut_Write/**/(_T("╚════════════════════════════════════════════════════════════════════════════════════════╝"));
}

static bool MainMenuOptionHandler(OptionHandlerArgs) {
	IgnoreUnused(extraInfo);
	switch (option) {
		case 'N':
			*action = &NewOrder_Menu;
			return true;
		case 'M':
			if (Orders_GetOpenCount() == 0) {
				*errorMsg = _T("No hay mesas abiertas");
				return false;
			}
			*action = &ModifyOrder_Menu;
			return true;
		case 'F':
			// TODO
			return true;
		case 'S':
			SystemEnd();
	}
	return false;
}

_Noreturn void MainMenu(void) {
	do {
		// TODO: Imprimir solo el panel izquierdo
		PrintMainMenu();
		HandleOptions(&MainMenuOptions, MainMenuOptionHandler);
		ConsoleOut_NewLineRepeat(2);
	} while (true);
}
