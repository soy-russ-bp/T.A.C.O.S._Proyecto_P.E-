#include "ModifyOrder.h"
#include "TableSelection.h"

void ModifyOrder_Menu(void) {
	int selectedTable = TableSelection_Menu(true);
	(void)selectedTable;
}
