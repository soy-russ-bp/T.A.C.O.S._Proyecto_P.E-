#include "Logo.h"
#include "ConsoleOut.h"
#include "ConsoleCursor.h"
#include "ConsoleStyle.h"

#define LogoPadding 24
#define LogoTitlePadding (LogoPadding + 2)

static void Logo_PrintTitle(void) {
	ConsoleCursor_MoveX(LogoTitlePadding);
	ConsoleStyle_Set(FOREGROUND_BRIGHT_WHITE | COMMON_LVB_UNDERSCORE);
	ConsoleOut_WriteLine(_T("Total Automated Customer Ordering System"));
}

static void Logo_PrintLogoLine(const TSTR line) {
	Logo_AddPadding();
	ConsoleOut_WriteLine(line);
}

void Logo_Print(void) {
	ConsoleOut_NewLineRepeat(10);
	ConsoleStyle_Set(FOREGROUND_BRIGHT_WHITE);
	Logo_PrintLogoLine(_T("████████╗ █████╗  ██████╗ ██████╗ ███████╗"));
	Logo_PrintLogoLine(_T("╚══██╔══╝██╔══██╗██╔════╝██╔═══██╗██╔════╝"));
	Logo_PrintLogoLine(_T("   ██║   ███████║██║     ██║   ██║███████╗"));
	Logo_PrintLogoLine(_T("   ██║   ██╔══██║██║     ██║   ██║╚════██║"));
	Logo_PrintLogoLine(_T("   ██║   ██║  ██║╚██████╗╚██████╔╝███████║"));
	Logo_PrintLogoLine(_T("   ╚═╝   ╚═╝  ╚═╝ ╚═════╝ ╚═════╝ ╚══════╝"));
	ConsoleOut_NewLine();
	Logo_PrintTitle();
	ConsoleStyle_Reset();
}

void Logo_AddPadding(void) {
	ConsoleCursor_MoveX(LogoPadding);
}
