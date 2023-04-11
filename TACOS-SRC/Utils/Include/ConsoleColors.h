#include "Flags.h"
#pragma once
#include <consoleapi2.h>

//
#define BrightBack(color) (color | BACKGROUND_INTENSITY)

//
#define BrightFore(color) (color | FOREGROUND_INTENSITY)

// Fondo blanco.
#define BACKGROUND_WHITE (BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE)

// Caracteres blancos.
#define FOREGROUND_WHITE (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)

// Caracteres blancos brillante.
#define FOREGROUND_BRIGHT_WHITE BrightFore(FOREGROUND_WHITE)

// Caracteres amarillos.
#define FOREGROUND_YELLOW (FOREGROUND_RED | FOREGROUND_GREEN)

// Caracteres amarillos brillante.
#define FOREGROUND_BRIGHT_YELLOW BrightFore(FOREGROUND_YELLOW)
