#include "Flags.h"
#pragma once
#include "StringMap.h"

#define FORMAT_DEC_BUILD_INIT _T("%.0f\0")

#define StrFormat_CalcLength(format, ...) _sctprintf(format, __VA_ARGS__)

void StrFormat_FillDecFormat(_Inout_ TSTR format, BYTE decimals);
