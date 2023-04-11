#include "ConsoleWidePrint.h"

#ifdef WidePrint

#include <stdio.h>
#include <locale.h>
#include <io.h>
#include <fcntl.h>
#include "Exceptions.h"

void EnableWidePrint(void) {
	setlocale(LC_ALL, "");
	int setmodeResult = _setmode(_fileno(stdout), _O_U16TEXT);
	Assert(setmodeResult != -1, "Error setting wide print.");
}

#endif
