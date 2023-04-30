#include "ConsoleIn.h"
#include <conio.h>
#include <ctype.h>
#include "ConsoleOut.h"
#include "CharUtils.h"

// Obtiene un carácter de la consola sin imprimirlo, incluyendo teclas extendidas.
static TCHINT ConsoleIn_GetRawChar(void) {
	return _gettch();
}

TCHAR ConsoleIn_GetCharNoEcho(void) {
	do {
		TCHINT ch = ConsoleIn_GetRawChar();
		if (!CharUtils_IsExtendedKey(ch)) {
			return (ch == '\r') ? '\n' : (TCHAR)ch;
		}
		ConsoleIn_GetRawChar();
	} while (true);
}

void ConsoleIn_WaitForChar(TCHAR ch) {
	while (ch != ConsoleIn_GetCharNoEcho());
}

void ConsoleIn_WaitForEnter(void) {
	ConsoleIn_WaitForChar('\n');
}

TCHAR GetSingleSubmitChar(CharFilter filter) {
	do {
		TCHAR ch1 = ConsoleIn_GetCharNoEcho();
		if (iscntrl(ch1) || !filter(&ch1)) continue;
		ConsoleOut_WriteChar(ch1);
		do {
			TCHAR ch2 = ConsoleIn_GetCharNoEcho();
			if (ch2 == '\b') {
				ConsoleOut_Backspace();
				break;
			}
			if (ch2 == '\n') return ch1;
		} while (true);
	} while (true);
}
