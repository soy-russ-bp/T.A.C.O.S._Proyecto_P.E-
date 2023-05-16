#include "ConsoleSize.h"
#include <windef.h>
#include <WinUser.h>
#include <debugapi.h>
#include "Exceptions.h"
#include "ConsoleConfig.h"

static short buffSizeOffset, windowSizeOffset;

// Establece el tamaño del buffer de la consola.
static void ConsoleSize_SetBufferSize(short width, short height) {
	COORD newScreenBuffSize = { width + buffSizeOffset, height };
	BOOL succeeded = SetConsoleScreenBufferSize(ConsoleOutHandle, newScreenBuffSize);
	Assert(succeeded, "Error setting console buffer size");
}

// Establece el tamaño de la ventana de la consola sin agregar ningún tipo de compensación.
static void ConsoleSize_SetWindowSizeNoOffset(short width, short height) {
	SMALL_RECT window = { 0, 0, width, height };
	BOOL succeeded = SetConsoleWindowInfo(ConsoleOutHandle, TRUE, &window);
	Assert(succeeded, "Error setting console window size");
}

// Establece el tamaño de la ventana de la consola, aplicando una compensación,
// para que el tamaño del búfer (de la consola) coincida con la cantidad de caracteres.
static void ConsoleSize_SetWindowSize(short width, short height) {
	ConsoleSize_SetWindowSizeNoOffset(width - windowSizeOffset, height - 1);
}

// Llamar antes de modificar el tamaño del buffer y ventana.
static void ConsoleSize_StartResize(void) {
	ConsoleSize_SetWindowSizeNoOffset(1, 1);
}

void ConsoleSize_Init(void) {
	if (IsDebuggerPresent()) windowSizeOffset = 1;
	else buffSizeOffset = 1;
}

void ConsoleSize_DisableResize(void) {
	LONG_PTR windowPtr = ConsoleConfig_GetWindowLongPtr(GWL_STYLE);
	LONG_PTR windowNewPtr = windowPtr & ~(WS_MAXIMIZEBOX | WS_SIZEBOX);
	ConsoleConfig_SetWindowLongPtr(GWL_STYLE, windowNewPtr);
}

void ConsoleSize_Set(short width, short height) {
	ConsoleSize_StartResize();
	ConsoleSize_SetBufferSize(width, height);
	ConsoleSize_SetWindowSize(width, height);
}

void ConsoleSize_SetAndLock(short width, short height) {
	ConsoleSize_DisableResize();
	ConsoleSize_Set(width, height);
}
