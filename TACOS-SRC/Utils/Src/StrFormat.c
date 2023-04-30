#include "StrFormat.h"
#include "Exceptions.h"
#include "CharUtils.h"
#include <float.h>

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
