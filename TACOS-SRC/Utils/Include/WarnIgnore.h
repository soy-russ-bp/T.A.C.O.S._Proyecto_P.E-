#include "Flags.h"
#pragma once
#include "MacroUtils.h"

#define WarnId_ExpectedStringLiteral 4774

#define WarnIgnore_UnusedVar(var) (void)(var)

#define WarnIgnore_CastDropQualifiers(exp) \
    ClangDiagnostic(push) \
    ClangDiagnostic(ignored "-Wcast-qual") \
    exp \
    ClangDiagnostic(pop)

#define WarnIgnore_Suppress(warnId) \
    __pragma(warning( suppress: warnId ))

#define WarnIgnore_SuppressIn(warnId) \
    WarnIgnore_Suppress(warnId) \
    MACROEND

#define WarnIgnore_AddedPadding_S \
	__pragma(warning( push )) \
    __pragma(warning( disable : 4820 ))

#define WarnIgnore_AddedPadding_E \
    __pragma(warning( pop ))
