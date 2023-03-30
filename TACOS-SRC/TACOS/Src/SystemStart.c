#include "SystemStart.h"
#include "ConsoleOut.h"
#include "ConsoleCursor.h"
#include "Sounds.h"
#include "Logo.h"
#include "Beep.h"
#include "Sleep.h"
#include "MainMenu.h"

static COORD PrintLoadingBarBase(void) {
	ConsoleOut_WriteChar('[');
	COORD barStartPos = ConsoleCursor_GetPos();
	ConsoleCursor_MoveX(40);
	ConsoleOut_WriteChar(']');
	return barStartPos;
}

static COORD LoadingAnimSetup(void) {
	ConsoleOut_NewLineRepeat(2);
	Logo_AddPadding();
	BeepSec(3000, 0.5);
	COORD barStartPos = PrintLoadingBarBase();
	COORD afterBarPos = ConsoleCursor_GetPos();
	ConsoleCursor_SetPos(barStartPos);
	return afterBarPos;
}

static void LoadingBarFill(void) {
	for (int i = 0; i < 40; i++) {
		ConsoleOut_WriteChar('/');
		SleepSec(.025);
	}
}

static void LoadingAnim(void) {
	COORD endPos = LoadingAnimSetup();
	LoadingBarFill();
	ConsoleCursor_SetPos(endPos);
	Sounds_PlayBoot();
	ConsoleOut_NewLine();
}

static void BootSequence(void) {
	Logo_Print();
	LoadingAnim();
}

_Noreturn void SystemStart(void) {
	BootSequence();
	MainMenu();
}
