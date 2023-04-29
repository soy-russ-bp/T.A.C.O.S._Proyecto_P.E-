#include "ConsoleCursor.h"
#include "ConsoleConfig.h"

COORD ConsoleCursor_GetPos(void) {
	ConsoleBufferInfo info;
	ConsoleConfig_FillConsoleBufferInfo(&info);
	return info.dwCursorPosition;
}

void ConsoleCursor_SetPos(COORD pos) {
	SetConsoleCursorPosition(ConsoleOutHandle, pos);
}

void ConsoleCursor_SetPos2(SHORT x, SHORT y) {
	ConsoleCursor_SetPos((COORD) { x, y });
}

void ConsoleCursor_MoveX(SHORT xOffset) {
	if (xOffset == 0) return;
	COORD currentPos = ConsoleCursor_GetPos();
	ConsoleCursor_SetPos2(currentPos.X + xOffset, currentPos.Y);
}

void ConsoleCursor_ResetPos(void) {
	ConsoleCursor_SetPos2(0, 0);
}
