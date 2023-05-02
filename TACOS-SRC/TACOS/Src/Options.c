#include "Options.h"
#include <wincontypes.h>
#include "ConsoleIn.h"
#include "ConsoleOut.h"
#include "ConsoleCursor.h"
#include "ConsoleStyle.h"
#include "CharUtils.h"
#include "TextLayout.h"
#include "Sleep.h"
#include "Exceptions.h"

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

static void PrintSubmittedInvalidOption(_In_opt_ TSTR errorMsg) {
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
	return ConsoleIn_GetSingleSubmitChar(UpperLetterOrNumFilter);
}

static void GetOptionStrSubmit(TSTR inputBuf, size_t bufSize) {
	ConsoleCursor_SetPos(OptionWriteCursorPos);
	ConsoleIn_GetFixedSubmitStr(inputBuf, bufSize, UpperLetterOrNumFilter);
}

void HandleStrOptions(TSTR inputBuf, size_t bufSize, const OptionGroup* optionGroup, OptionHandler optionHandler) {
	HandleStrOptionsExtra(inputBuf, bufSize, optionGroup, optionHandler, NULL);
}

void HandleStrOptionsExtra(TSTR inputBuf, size_t bufSize, const OptionGroup* optionGroup, OptionHandler optionHandler, _Inout_opt_ void* extraInfo) {
	PrintOptions(optionGroup);
	bool inputIsChar = (bufSize == 1);
	Action navAction;
	do {
		OptionInput optionInput = { 0 };
		if (inputIsChar) {
			optionInput.single = GetOptionSubmit();
		} else {
			AssertNotNull(inputBuf);
			GetOptionStrSubmit(inputBuf, bufSize);
			optionInput.string = inputBuf;
		}
		navAction = NULL;
		TSTR errorMsg = NULL;
		bool isValidOption = optionHandler(optionInput, &navAction, &errorMsg, extraInfo);
		if (isValidOption) break;
		else PrintSubmittedInvalidOption(errorMsg);
	} while (true);
	if (inputIsChar) ConsoleOut_Backspace();
	else ConsoleOut_BackspaceRepeat(bufSize - 1);
	Action_TryExecute(navAction);
}

void HandleOptions(const OptionGroup* optionGroup, OptionHandler optionHandler) {
	HandleOptionsExtra(optionGroup, optionHandler, NULL);
}

void HandleOptionsExtra(const OptionGroup* optionGroup, OptionHandler optionHandler, _Inout_opt_ void* extraInfo) {
	HandleStrOptionsExtra(NULL, 1, optionGroup, optionHandler, extraInfo);
}
