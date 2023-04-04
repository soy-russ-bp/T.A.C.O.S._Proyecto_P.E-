#include "NewOrder.h"
#include <wincontypes.h>
#include "StringMap.h"
#include "ArrayUtils.h"
#include "CharUtils.h"
#include "ConsoleOut.h"
#include "ConsoleCursor.h"
#include "ConsoleStyle.h"
#include "Sounds.h"
#include "Options.h"
#include "Orders.h"

static const TSTR NewOrderOptionsList[] = { _T("~#Sel. número de mesa") };
static const OptionGroup NewOrderOptions = { StaticArrayAndLength(NewOrderOptionsList), OTReturn };
static const COORD Row1TablesPos = { 4, 2 };
static const COORD Row2TablesPos = { 4, 2 + 6 };
#define TableAvailabilityDisplayLen 8

static void FillLeftPanelRow(TCHAR startCh, TCHAR contentCh, TCHAR endCh) {
	ConsoleOut_WriteChar(startCh);
	ConsoleOut_WriteCharRepeat(contentCh, 58);
	ConsoleOut_WriteChar(endCh);
	ConsoleOut_NewLine();
}

static void BlankLeftPanelRow(void) {
	FillLeftPanelRow(L'║', ' ', L'║');
}

static void FillLeftPanelForNewOrderMenu(void) {
	FillLeftPanelRow(L'╔', L'═', L'╦');
	for (int i = 0; i < 13; i++) BlankLeftPanelRow();
	for (int i = 0; i < 2; i++) {
		FillLeftPanelRow(L'╠', L'═', L'╣');
		BlankLeftPanelRow();
	}
	FillLeftPanelRow(L'╠', L'═', L'╩');
}

static void PrintTableDisplayRow(TCHAR wallCh, TCHAR contentCh, ConsoleStyle style) {
	ConsoleOut_WriteChar(wallCh);
	if (style) ConsoleStyle_Set(style);
	ConsoleOut_WriteCharRepeat(contentCh, TableAvailabilityDisplayLen);
	if (style) ConsoleStyle_Reset();
	ConsoleOut_WriteChar(wallCh);
}

static void PrintTableDisplayRowT1(void) {
	PrintTableDisplayRow('+', '-', 0);
}

static void PrintTableDisplayRowT2(ConsoleStyle style) {
	PrintTableDisplayRow('|', ' ', style);
}

static void PrintTableNum(COORD tablePos, size_t tableNum) {
	COORD numPos = (COORD){ tablePos.X + 4, tablePos.Y + 1 };
	ConsoleCursor_SetPos(numPos);
	ConsoleOut_WriteFormat(_T("0%d"), (int)tableNum);
}

static void PrintTable(COORD tablePos, size_t tableNum) {
	ConsoleCursor_SetPos(tablePos);
	PrintTableDisplayRowT1();
	Table* table = Orders_GetTableByNum(tableNum);
	ConsoleStyle tableColor = Orders_GetTableStatusColor(table);
	for (int i = 0; i < 2; i++) {
		tablePos.Y++;
		ConsoleCursor_SetPos(tablePos);
		PrintTableDisplayRowT2(tableColor);
	}
	tablePos.Y++;
	ConsoleCursor_SetPos(tablePos);
	PrintTableDisplayRowT1();
	PrintTableNum(tablePos, tableNum);
}

static void PrintTableRow(COORD rowPos, size_t tableStartNum) {
	for (int i = 0; i < 4; i++) {
		PrintTable(rowPos, tableStartNum++);
		rowPos.X += 10 + 4;
	}
}

static void PrintNewOrderMenu(void) {
	ConsoleCursor_ResetPos();
	FillLeftPanelForNewOrderMenu();
	PrintTableRow(Row1TablesPos, 1);
	PrintTableRow(Row2TablesPos, 5);
}
static COORD GetTableRowPos(int tableNum) {
	return (tableNum <= 4) ? Row1TablesPos : Row2TablesPos;
}

static short GetInRowIndex(int tableNum) {
	return (tableNum - 1) % 4;
}

static COORD GetAvailabilityDisplayPos(int tableNum) {
	COORD pos = GetTableRowPos(tableNum);
	short inRowI = GetInRowIndex(tableNum);
	short x = (pos.X + 1) + (inRowI * 14);
	short y = pos.Y + 1;
	return (COORD) { x, y };
}

static void ShowTableAsOccupied(int tableNum) {
	COORD oldPos = ConsoleCursor_GetPos();
	COORD pos = GetAvailabilityDisplayPos(tableNum);
	ConsoleStyle_Set(TableOccupiedColor);
	for (int i = 0; i < 2; i++) {
		ConsoleCursor_SetPos(pos);
		ConsoleOut_WriteCharRepeat(' ', TableAvailabilityDisplayLen);
		pos.Y++;
	}
	ConsoleStyle_Reset();
	ConsoleCursor_SetPos(oldPos);
	Sounds_PlaySelect();
}

static bool NewOrderOptionHandler(OptionHandlerArgs) {
	(void)action;
	{
		BYTE tableNum;
		if (CharUtils_IsAsciiDigitOut(option, &tableNum)) {
			bool assigned = Orders_TryAssignTable(tableNum, errorMsg);
			if (assigned) {
				ShowTableAsOccupied(tableNum);
				SleepSec(.5);
			}
			return assigned;
		}
	}
	if (option == 'R') return true;
	return false;
}

void NewOrder_Menu(void) {
	PrintNewOrderMenu();
	HandleOptions(&NewOrderOptions, NewOrderOptionHandler);
}
