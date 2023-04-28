#include "Options.h"
#include <wincontypes.h>
#include "ConsoleIn.h"
#include "ConsoleOut.h"
#include "ConsoleCursor.h"
#include "ConsoleStyle.h"
#include "CharUtils.h"
#include "TextLayout.h"
#include "Sleep.h"

#define Max_Options 5
#define OptionMaxLen 19
#define OPT_AREA_X 62
#define OPT_AREA_Y 4
static const TSTR InvalidOptionMsg = _T("Opción invalida");
static const COORD OptionWriteCursorPos = { 10, 28 };
static const COORD MenuOptionsTitlePos = { OPT_AREA_X, OPT_AREA_Y };
static const COORD MenuOptionsListPos = { OPT_AREA_X + 1, OPT_AREA_Y + 2 };
static const COORD MenuOptionsExitPos = { OPT_AREA_X + 1, OPT_AREA_Y + 12 };
static const int TitleLengthOffset = 4; // "◄ " + " ►"
#define ErrorMsgSeparator _T(" - ")
#define ErrorMsgLenOffset 4 // (StaticStrlen(ErrorMsgSeparator) + 1)

static void AddOptionGroupTitleLeftPad(TSTR title) {
	size_t titleLength = TStrLen(title) + TitleLengthOffset;
	short leftPad = (short)TextLayout_CenterTextLeftPadding(titleLength, 27);
	ConsoleCursor_MoveX(leftPad);
}

static TSTR GetOptionGroupTitle(OptionType optionType) {
	switch (optionType) {
		case OTConfirmExit: return _T("Salir?");
		default: return _T("Acción");
	}
}

static void PrintOptionGroupTitle(OptionType optionType) {
	TSTR title = GetOptionGroupTitle(optionType);
	AddOptionGroupTitleLeftPad(title);
	ConsoleOut_Write(_T("◄ "));
	ConsoleOut_Write(title);
	ConsoleOut_Write(_T(" ►"));
	ConsoleOut_NewLine();
}

static void GetOptionGroupOptionDisplay(_Out_ TCHAR* ch, _Inout_ TSTR* text) {
	TCHAR firstCh = (*text)[0];
	if (firstCh == '~') {
		*ch = (*text)[1];
		*text += 2;
	} else {
		*ch = firstCh;
	}
}

static void ClearLastOptionLinePrint(TSTR option) {
	size_t lenToClear = OptionMaxLen - TStrLen(option);
	ConsoleOut_WriteCharRepeatStyled(' ', lenToClear, FOREGROUND_WHITE);
}

static void PrintOptionGroupOptionLine(TSTR option, COORD pos) {
	ConsoleCursor_SetPos(pos);
	TCHAR ch;
	GetOptionGroupOptionDisplay(&ch, &option);
	ConsoleOut_WriteFormat(_T(" %c - %s "), ch, option);
	ClearLastOptionLinePrint(option);
}

static TSTR TryGetOptionGroupTypeOption(OptionType optionType) {
	switch (optionType) {
		case OTReturn: return _T("Regresar");
		case OTExit: return _T("Salir");
		default: return NULL;
	}
}

static void PrintOptionGroupTypeOption(OptionType optionType) {
	TSTR typeOpt = TryGetOptionGroupTypeOption(optionType);
	if (typeOpt == NULL) return;
	ConsoleStyle_Set(BrightBack(BACKGROUND_RED) | FOREGROUND_BRIGHT_YELLOW);
	PrintOptionGroupOptionLine(typeOpt, MenuOptionsExitPos);
}

static void ClearPreviousOptionGroupOptions(int optionCountCurrGroup, COORD optionPos) {
	ConsoleStyle_Reset();
	int rowsToClear = Max_Options - optionCountCurrGroup;
	for (int i = 0; i < rowsToClear; i++) {
		ConsoleCursor_SetPos(optionPos);
		ConsoleOut_WriteCharRepeat(' ', 22);
		optionPos.Y += 2;
	}
}

static void PrintOptionGroupOptions(const OptionGroup* optionGroup) {
	const int optionCount = optionGroup->optionCount;
	const TSTR* options = optionGroup->options;
	COORD optionPos = MenuOptionsListPos;
	ConsoleStyle_Set(BrightBack(BACKGROUND_GREEN) | FOREGROUND_BRIGHT_YELLOW);
	for (int i = 0; i < optionCount; i++) {
		PrintOptionGroupOptionLine(options[i], optionPos);
		optionPos.Y += 2;
	}
	ClearPreviousOptionGroupOptions(optionCount, optionPos);
	PrintOptionGroupTypeOption(optionGroup->optionType);
	ConsoleStyle_Reset();
}

static void PrintOptions(const OptionGroup* optionGroup) {
	ConsoleCursor_SetPos(MenuOptionsTitlePos);
	PrintOptionGroupTitle(optionGroup->optionType);
	PrintOptionGroupOptions(optionGroup);
}

static void PrintSubmittedInvalidOption(TSTR errorMsg) {
	if (errorMsg == NULL) errorMsg = InvalidOptionMsg;// TODO
	ConsoleOut_Write(ErrorMsgSeparator);
	ConsoleOut_WriteStyled(errorMsg, BrightBack(BACKGROUND_RED) | BrightFore(FOREGROUND_WHITE));
	SleepSec(1.5);
	ConsoleCursor_SetPos(OptionWriteCursorPos);
	ConsoleOut_WriteCharRepeat(' ', TStrLen(errorMsg) + ErrorMsgLenOffset);
}

static bool UpperLetterOrNumFilter(TCHAR* inputChPtr) {
	TCHAR inputCh = *inputChPtr;
	if (CharUtils_IsAsciiAlpha(inputCh)) {
		*inputChPtr = (TCHAR)_totupper(inputCh);
		return true;
	}
	if (CharUtils_IsAsciiDigit(inputCh)) return true;
	return false;
}

static TCHAR GetOptionSubmit(void) {
	ConsoleCursor_SetPos(OptionWriteCursorPos);
	return GetSingleSubmitChar(UpperLetterOrNumFilter);
}

void HandleOptions(const OptionGroup* optionGroup, OptionHandler optionHandler) {
	HandleOptionsExtra(optionGroup, optionHandler, NULL);
}

void HandleOptionsExtra(const OptionGroup* optionGroup, OptionHandler optionHandler, _Inout_opt_ void* extraInfo) {
	PrintOptions(optionGroup);
	Action optionAction = NULL;
	do {
		TCHAR option = GetOptionSubmit();
		TSTR errorMsg = NULL;
		bool isValidOption = optionHandler(option, &optionAction, &errorMsg, extraInfo);
		if (isValidOption) break;
		else PrintSubmittedInvalidOption(errorMsg);
	} while (true);
	ConsoleOut_Backspace();
	Action_TryExecute(optionAction);
}
