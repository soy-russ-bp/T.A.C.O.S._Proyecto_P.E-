#include "ModificarOrden.h"
#include "NewOrder.h"
#include "ConsoleOut.h" //módulo para imprimir
#include "ConsoleCursor.h"
#include "Sleep.h"

static void PrintModulo_ModificarOrden(void) {
	ConsoleCursor_SetPos2(50, 10);
	ConsoleOut_Write(_T("+"));
	SleepSec(5);
}

static void PrintModifyOrderMenu(void) {
	PrintTablesStatusPanel(true);
}

void ModifyOrder_Menu(void) {
	//PrintModulo_ModificarOrden();
	PrintModifyOrderMenu();
	SleepSec(100);
}