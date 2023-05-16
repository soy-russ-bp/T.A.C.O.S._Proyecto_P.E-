#include "NewOrder.h"
#include "TableSelection.h"
#include "ModifyOrder.h"

void NewOrder_Menu(void) {
	int selectedTable = TableSelection_Menu(false);
	ModifyOrder_TryTansferToMenu(selectedTable);
}
