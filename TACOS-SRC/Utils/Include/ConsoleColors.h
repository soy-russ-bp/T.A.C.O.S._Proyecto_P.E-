#include "Flags.h"
#pragma once
#include <consoleapi2.h>

//
#define BrightBack(color) (color | BACKGROUND_INTENSITY)

//
#define BrightFore(color) (color | FOREGROUND_INTENSITY)

// Car�cteres blancos.
#define FOREGROUND_WHITE (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)

// Car�cteres blancos brillante.
#define FOREGROUND_BRIGHT_WHITE BrightFore(FOREGROUND_WHITE)

// Car�cteres amarillos.
#define FOREGROUND_YELLOW (FOREGROUND_RED | FOREGROUND_GREEN)

// Car�cteres amarillos brillante.
#define FOREGROUND_BRIGHT_YELLOW BrightFore(FOREGROUND_YELLOW)
