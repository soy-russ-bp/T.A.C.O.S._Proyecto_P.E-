#include "Flags.h"
#pragma once

#define WarnIgnore_UnusedVar(var) (void)(var)

#define WarnIgnore_AddedPadding_S \
	__pragma(warning( push )) \
    __pragma(warning( disable : 4820 ))

#define WarnIgnore_AddedPadding_E \
    __pragma(warning( pop ))
