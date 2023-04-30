#include "CloseOrder.h"
#include "StringMap.h"
#include "ArrayUtils.h"
#include "ConsoleOut.h"
#include "ConsoleCursor.h"
#include "Sleep.h"
#include "WarnIgnore.h"
#include "Options.h"

// TODO
static const TSTR CloseOrderMenuOptionsList[] = { _T("Opc 1"), _T("Opc 2"), _T("123") };
static const OptionGroup CloseOrderOptions = { StaticArrayAndLength(CloseOrderMenuOptionsList), OTReturn };

static bool CloseOrderOptionHandler(OptionHandlerArgs) {
	// TODO
	// OptionHandlerArgs: TCHAR option, Action* action, TSTR* errorMsg, void* extraInfo
	WarnIgnore_UnusedVar(optionInput);
	WarnIgnore_UnusedVar(navAction);
	WarnIgnore_UnusedVar(extraInfo);
	// ---
	*errorMsg = _T("Por implementar");
	return false;
}

static void PrintCloseOrderMenu(void) {
	// TODO
	ConsoleCursor_ResetPos();
	ConsoleOut_Write(_T("TEST"));
}

void CloseOrder_Menu(void) {
	// TODO
	PrintCloseOrderMenu();
	HandleOptions(&CloseOrderOptions, CloseOrderOptionHandler);
	SleepSec(5);
}
