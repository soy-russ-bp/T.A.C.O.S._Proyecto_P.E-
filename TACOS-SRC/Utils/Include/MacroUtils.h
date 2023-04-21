#include "Flags.h"
#pragma once

#define MACROEND ((void)(0))

#define P_TOSTRING(x) #x
#define TOSTRING(x) P_TOSTRING(x)

#define P_TCONCAT(T1, T2) T1 ## T2
#define TCONCAT(T1, T2) P_TCONCAT(T1, T2)
