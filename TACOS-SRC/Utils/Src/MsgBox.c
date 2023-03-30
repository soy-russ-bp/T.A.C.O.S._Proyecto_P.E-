#include "MsgBox.h"
#include <WinUser.h>

void MsgBox_ErrorA(LPCSTR title, LPCSTR content) {
	MessageBoxA(NULL, content, title, MB_ICONERROR | MB_SETFOREGROUND | MB_TASKMODAL);
}
