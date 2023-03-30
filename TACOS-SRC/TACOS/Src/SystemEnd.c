#include "SystemEnd.h"
#include "stdlib.h"
#include "ConsoleIn.h"
#include "ConsoleOut.h"
#include "Logo.h"
#include "Sounds.h"

static void ExitEnterWait(void) {
    ConsoleOut_WriteCharRepeat('\n', 3);
    ConsoleOut_WriteCharRepeat(' ', 3);
    ConsoleOut_Write(_T("Presione enter para salir del programa..."));
    ConsoleIn_WaitForEnter();
}

_Noreturn void SystemEnd(void) {
    ConsoleOut_Clear();
    Logo_Print();
    Sounds_PlaySystemEnd();
    ExitEnterWait();
	exit(0);
}
