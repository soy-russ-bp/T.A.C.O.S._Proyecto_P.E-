#include "Flags.h"
#pragma once
#include "StringMap.h"

// Determina si un carácter es el inicio de una teclas extendida.
bool CharUtils_IsExtendedKey(TCHINT ch);

bool CharUtils_IsAsciiAlpha(TCHAR ch);

bool CharUtils_IsAsciiDigit(TCHAR ch);

_Success_(OnTrueReturn) bool CharUtils_IsAsciiDigitOut(TCHAR ch, _Out_ BYTE* digit);

TCHAR CharUtils_ToAsciiDigit(BYTE digitAsNum);
