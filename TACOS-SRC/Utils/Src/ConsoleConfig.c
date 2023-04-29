#include "ConsoleConfig.h"
#include <consoleapi.h>
#include <consoleapi3.h>
#include <WinBase.h>
#include <WinUser.h>
#include "ConsoleWidePrint.h"
#include "ConsoleStyle.h"
#include "ConsoleSize.h"
#include "Exceptions.h"

HWND ConsoleWindow;
HANDLE ConsoleInHandle;
HANDLE ConsoleOutHandle;

void ConsoleConfig_Setup(void) {
	ConsoleWindow = GetConsoleWindow();
	ConsoleInHandle = GetStdHandle(STD_INPUT_HANDLE);
	ConsoleOutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
#ifdef WidePrint
	EnableWidePrint();
#endif
	ConsoleStyle_Reset();
	ConsoleSize_Init();
}

void ConsoleConfig_DisableTextSelect(void) {
	DWORD prev_mode;
	GetConsoleMode(ConsoleInHandle, &prev_mode);
	SetConsoleMode(ConsoleInHandle, ENABLE_EXTENDED_FLAGS | (prev_mode & ~(ULONG)ENABLE_QUICK_EDIT_MODE));
}

void ConsoleConfig_FillConsoleBufferInfo(ConsoleBufferInfo* consoleBufferInfo) {
	BOOL succeeded = GetConsoleScreenBufferInfo(ConsoleOutHandle, consoleBufferInfo);
	Assert(succeeded, "Error getting screen buffer info");
}

LONG_PTR ConsoleConfig_GetWindowLongPtr(int nIndex) {
	LONG_PTR windowPtr = GetWindowLongPtr(ConsoleWindow, nIndex);
	Assert(windowPtr, "Error getting window LongPtr");
	return windowPtr;
}

void ConsoleConfig_SetWindowLongPtr(int nIndex, LONG_PTR newLongPtr) {
	LONG_PTR setWindowPtrResult = SetWindowLongPtr(ConsoleWindow, nIndex, newLongPtr);
	Assert(setWindowPtrResult, "Error setting window LongPtr");
}
