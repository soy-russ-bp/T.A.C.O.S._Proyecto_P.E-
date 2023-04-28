#include "ConsoleOut.h"
#include <stdlib.h>
#include "ConsoleCursor.h"
#include "MathUtils.h"
#include "TextLayout.h"

void ConsoleOut_Write(const TSTR str) {
	_fputts(str, stdout);
}

void ConsoleOut_WriteLine(const TSTR str) {
	ConsoleOut_Write(str);
	ConsoleOut_NewLine();
}

void ConsoleOut_WriteStyled(const TSTR str, ConsoleStyle style) {
	ConsoleStyle oldStyle = ConsoleStyle_Get();
	ConsoleStyle_Set(style);
	ConsoleOut_Write(str);
	ConsoleStyle_Set(oldStyle);
}

void ConsoleOut_WriteChar(TCHAR ch) {
	_puttchar(ch);
}

void ConsoleOut_WriteCharRepeat(TCHAR ch, size_t repeatCount) {
	while (repeatCount--) ConsoleOut_WriteChar(ch);
}

void ConsoleOut_WriteCharRepeatStyled(TCHAR ch, size_t repeatCount, ConsoleStyle style) {
	ConsoleStyle oldStyle = ConsoleStyle_Get();
	ConsoleStyle_Set(style);
	ConsoleOut_WriteCharRepeat(ch, repeatCount);
	ConsoleStyle_Set(oldStyle);
}

void ConsoleOut_WriteUInt(UINT num) {
	ConsoleOut_WriteFormat(_T("%u"), num);
}

void ConsoleOut_WriteCenteredUInt(UINT num, size_t width) {
	size_t leftPad, rightPad;
	size_t digitCount = Math_DigitCount((int)num);
	TextLayout_CenterTextPadding(digitCount, width, &leftPad, &rightPad);
	ConsoleCursor_MoveX((SHORT)leftPad);
	ConsoleOut_WriteUInt(num);
	ConsoleCursor_MoveX((SHORT)rightPad);
}

void ConsoleOut_NewLine(void) {
	ConsoleOut_WriteChar('\n');
}

void ConsoleOut_NewLineRepeat(size_t repeatCount) {
	while (repeatCount--) ConsoleOut_NewLine();
}

void ConsoleOut_Backspace(void) {
	ConsoleOut_Write(_T("\b \b"));
}

void ConsoleOut_Clear(void) {
	system("cls");
}
