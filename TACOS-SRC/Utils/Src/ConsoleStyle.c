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

ConsoleStyle ConsoleStyle_GetSet(ConsoleStyle style) {
	ConsoleStyle oldStyle = ConsoleStyle_Get();
	ConsoleStyle_Set(style);
	return oldStyle;
}

void ConsoleStyle_Reset(void) {
	ConsoleStyle_Set(FOREGROUND_WHITE);
}
