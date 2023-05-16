#include "Main.h"

static void ConsoleSetup(void) {
	ConsoleConfig_Setup();
	SetConsoleTitleA("TACOS");
#ifndef _DEBUG
	ConsoleConfig_DisableTextSelect();
#endif
	ConsoleSize_SetAndLock(90, 30);
}

int Main(void) {
	ConsoleSetup();
	SystemStart();
}
