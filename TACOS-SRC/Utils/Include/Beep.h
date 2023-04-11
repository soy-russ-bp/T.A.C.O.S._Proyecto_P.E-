#include "Flags.h"
#pragma once
#include "MathUtils.h"

#ifndef NoBeep

#include <utilapiset.h>

#else

#include "Sleep.h"

#define Beep(freq, ms) Sleep(ms)

#endif

#define BeepSec(freq, secs) Beep(freq, Math_SecToMs(secs))
