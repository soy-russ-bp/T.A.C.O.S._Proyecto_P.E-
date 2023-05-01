#include "Flags.h"
#pragma once
#include <malloc.h>
#include "StringMap.h"
#include "WarnIgnore.h"
#include "TextLayout.h"

#define FORMAT_DEC_BUILD_INIT _T("%.0f\0")

#define StrFormat_CalcLength(format, ...) _sctprintf(format, __VA_ARGS__)

void StrFormat_FillDecFormat(_Inout_ TSTR format, BYTE decimals);

#define StrFormat_FillFormat(buffer, format, ...) \
	_stprintf(buffer, format, __VA_ARGS__);

TSTR StrFormat_FillAndNullTerminate(TSTR str, TCHAR ch, size_t width);

TSTR StrFormat_Aligned(SalExt_Str_In_NotNull_ TSTR buffer, SalExt_Str_In_NotNull_ TSTR str, size_t width, TextAlignment alignment);

TSTR StrFormat_AlignedF(SalExt_Str_In_NotNull_ TSTR buffer, size_t width, TextAlignment alignment, SalExt_Str_In_NotNull_ TSTR format, ...);

size_t StrFormat_GetAllocSize(size_t allocSize);

#define RawStrStackAlloc(charCount) \
	WarnIgnore_Suppress(6255) \
	_alloca( StrFormat_GetAllocSize(charCount) )

#define SF_Align(text, width, alignment) \
	StrFormat_Aligned( \
		RawStrStackAlloc(width), \
		text, \
		width, \
		alignment \
	)

#define SF_AlignF(width, alignment, format, ...) \
	StrFormat_AlignedF( \
		RawStrStackAlloc( StrFormat_CalcLength(format, __VA_ARGS__) ), \
		width, \
		alignment, \
		format, \
		__VA_ARGS__ \
	)

#define SF_Repeat(ch, repeatTimes) \
	StrFormat_FillAndNullTerminate( \
		RawStrStackAlloc(repeatTimes), \
		ch, \
		repeatTimes \
	)
