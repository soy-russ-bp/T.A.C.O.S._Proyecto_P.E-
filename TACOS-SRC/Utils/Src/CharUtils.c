#include "CharUtils.h"
#include "MathUtils.h"
#include "Exceptions.h"

bool CharUtils_IsExtendedKey(TCHINT ch) {
	return (ch == 0 || ch == 0xE0);
}

bool CharUtils_IsAsciiAlpha(TCHAR ch) {
	return Math_IsInURange((UINT)ch, 'A', 'Z') || Math_IsInURange((UINT)ch, 'a', 'z');
}

bool CharUtils_IsAsciiDigit(TCHAR ch) {
	return Math_IsInURange((UINT)ch, '0', '9');
}

_Success_(OnTrueReturn) bool CharUtils_IsAsciiDigitOut(TCHAR ch, _Out_ BYTE* digit) {
	bool isDigit = CharUtils_IsAsciiDigit(ch);
	if (isDigit) *digit = (BYTE)(ch - '0');
	return isDigit;
}

TCHAR CharUtils_ToAsciiDigit(BYTE digitAsNum) {
	BYTE digit = digitAsNum + '0';
	Assert(CharUtils_IsAsciiDigit(digit), "Must have a numeric value in the range 1-9");
	return digit;
}
