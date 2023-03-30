#include "Flags.h"
#pragma once
#include <consoleapi2.h>

//
#define BrightBack(color) (color | BACKGROUND_INTENSITY)

//
#define BrightFore(color) (color | FOREGROUND_INTENSITY)

// Carácteres blancos.
#define FOREGROUND_WHITE (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)

// Carácteres blancos brillante.
#define FOREGROUND_BRIGHT_WHITE BrightFore(FOREGROUND_WHITE)

// Carácteres amarillos.
#define FOREGROUND_YELLOW (FOREGROUND_RED | FOREGROUND_GREEN)

// Carácteres amarillos brillante.
#define FOREGROUND_BRIGHT_YELLOW BrightFore(FOREGROUND_YELLOW)
