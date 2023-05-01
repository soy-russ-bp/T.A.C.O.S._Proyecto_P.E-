#include "StrFormat.h"
#include <float.h>
#include <stdarg.h>
#include "Exceptions.h"
#include "CharUtils.h"

static size_t lastAllocLen;

void StrFormat_FillDecFormat(_Inout_ TSTR format, BYTE decimals) {
	if (decimals == 0) return;
	Assert(decimals <= DBL_DIG, "Invalid decimal count. Max: " TOSTRING(DBL_DIG));
	bool twoDigits = decimals >= 10;
	if (twoDigits) {
		format[2] = '1';
		format[3] = CharUtils_ToAsciiDigit((BYTE)(decimals - 10));
		format[4] = 'f';
	} else {
		format[2] = CharUtils_ToAsciiDigit((BYTE)(decimals));
	}
}

TSTR StrFormat_FillAndNullTerminate(TSTR str, TCHAR ch, size_t width) {
	UnsafeMemSet(str, ch, width);
	str[width] = '\0';
	return str;
}

TSTR StrFormat_Aligned(SalExt_Str_In_NotNull_ TSTR buffer, SalExt_Str_In_NotNull_ TSTR str, size_t width, TextAlignment alignment) {
	size_t leftPad, rightPad;
	size_t textLength = TStrLen(str);
	TextLayout_AlignedTextPadding(textLength, width, alignment, &leftPad, &rightPad);
	UnsafeMemSet(buffer, ' ', leftPad);
	UnsafeMemCpy(&buffer[leftPad], str, textLength);
	UnsafeMemSet(&buffer[leftPad + textLength], ' ', rightPad);
	buffer[width] = '\0';
	return buffer;
}

TSTR StrFormat_AlignedF(SalExt_Str_In_NotNull_ TSTR buffer, size_t width, TextAlignment alignment, SalExt_Str_In_NotNull_ TSTR format, ...) {
	va_list args;
	va_start(args, format);
	size_t textLength = StrFormat_CalcLengthList(format, args);
	va_end(args);

	size_t leftPad, rightPad;
	TextLayout_AlignedTextPadding(textLength, width, alignment, &leftPad, &rightPad);
	UnsafeMemSet(buffer, ' ', leftPad);

	va_start(args, format);
	_vstprintf(&buffer[leftPad], lastAllocLen, format, args);
	va_end(args);

	UnsafeMemSet(&buffer[leftPad + textLength], ' ', rightPad);
	buffer[width] = '\0';
	return buffer;
}

size_t StrFormat_GetAllocSize(size_t charCount) {
	lastAllocLen = charCount;
	return (charCount + 1) * sizeof(TCHAR);
}
