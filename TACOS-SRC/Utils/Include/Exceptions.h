#include "Flags.h"
#pragma once
#include <stdlib.h>
#include <intrin.h>
#include "MacroUtils.h"
#include "MsgBox.h"
#include "ArrayUtils.h"

#ifdef _DEBUG

#define Throw(errorMsg) \
    MsgBox_ErrorA("Exception", "File: " __FILE__ ".\nLine: " TOSTRING(__LINE__) "\n\n" errorMsg "."); \
    __debugbreak(); \
    exit(EXIT_FAILURE)

#else

#define Throw(errorMsg) \
	MsgBox_ErrorA("Exception", (errorMsg)); \
    exit(EXIT_FAILURE)

#endif

#define Assert(exp, errorMsg) \
    if (!(exp)) { \
        Throw(errorMsg); \
    } \
    MACROEND

#define AssertIsInArrayBounds(index, size) \
    Assert(Array_IsInBounds(index, size), "Index is not in array bounds")

#define AssertNotNull(var) \
    Assert(var != NULL, "Variable is null")
