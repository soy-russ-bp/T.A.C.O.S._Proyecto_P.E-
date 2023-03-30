#include "ConsoleStyle.h"
#include "ConsoleConfig.h"

ConsoleStyle ConsoleStyle_Get(void) {
	ConsoleBufferInfo info;
	ConsoleConfig_FillConsoleBufferInfo(&info);
	return info.wAttributes;
}

void ConsoleStyle_Set(ConsoleStyle style) {
	SetConsoleTextAttribute(ConsoleOutHandle, style);
}

void ConsoleStyle_Reset(void) {
	ConsoleStyle_Set(FOREGROUND_WHITE);
}
