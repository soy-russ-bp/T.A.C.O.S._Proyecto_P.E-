#include "Main.h"

static void ConsoleSetup(void) {
	ConsoleConfig_Setup();
	SetConsoleTitleA("TACOS");
	ConsoleConfig_DisableTextSelect();
	ConsoleSize_SetAndLock(90, 30);
}

int Main(void) {
	ConsoleSetup();
	SystemStart();
}
