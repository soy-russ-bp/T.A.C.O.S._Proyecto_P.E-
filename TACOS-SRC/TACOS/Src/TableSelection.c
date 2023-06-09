﻿#include "TableSelection.h"
#include <wincontypes.h>
#include "StringMap.h"
#include "ArrayUtils.h"
#include "WarnIgnore.h"
#include "Exceptions.h"
#include "CharUtils.h"
#include "ConsoleOut.h"
#include "ConsoleCursor.h"
#include "ConsoleStyle.h"
#include "Sounds.h"
#include "Options.h"
#include "Orders.h"

static const TSTR TableSelectionOptionsList[] = { L"~#Sel. número de mesa" };
static const OptionGroup TableSelectionOptions = { StaticArrayAndLength(TableSelectionOptionsList), OTReturn };

static const COORD Row1TablesPos = { 4, 2 };
static const COORD Row2TablesPos = { 4, 2 + 6 };
#define TableAvailabilityDisplayLen 8

WarnIgnore_AddedPadding_S
typedef struct {
	_In_ bool onlyOccupied;
	_Out_ int selected;
} TableSelectionInfo;
WarnIgnore_AddedPadding_E

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

static ConsoleStyle GetTableSelectableStateColor(_In_ Table* table) {
	bool tableOccupied = Orders_IsTableOccupied(table);
	ConsoleStyle stateColor = tableOccupied ? BACKGROUND_WHITE : 0;
	return stateColor;
}

static ConsoleStyle GetTableColorInContext(_In_ Table* table, bool onlyOccupied) {
	ConsoleStyle tableColor = (onlyOccupied)
		? GetTableSelectableStateColor(table)
		: Orders_GetTableStatusColor(table);
	return tableColor;
}

static void PrintTable(COORD tablePos, size_t tableNum, bool onlyOccupied) {
	Table* table = Orders_GetTableByNum(tableNum);
	ConsoleCursor_SetPos(tablePos);
	PrintTableDisplayRowT1();
	ConsoleStyle tableColor = GetTableColorInContext(table, onlyOccupied);
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

static void PrintTableRow(COORD rowPos, size_t tableStartNum, bool onlyOccupied) {
	size_t tableNum = tableStartNum;
	for (int i = 0; i < 4; i++) {
		PrintTable(rowPos, tableNum++, onlyOccupied);
		rowPos.X += 10 + 4;
	}
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

static void SelectTableInMenu(int tableNum, ConsoleStyle selectStyle) {
	COORD oldPos = ConsoleCursor_GetPos();
	COORD pos = GetAvailabilityDisplayPos(tableNum);
	ConsoleStyle_Set(selectStyle);
	for (int i = 0; i < 2; i++) {
		ConsoleCursor_SetPos(pos);
		ConsoleOut_WriteCharRepeat(' ', TableAvailabilityDisplayLen);
		pos.Y++;
	}
	ConsoleStyle_Reset();
	ConsoleCursor_SetPos(oldPos);
	Sounds_PlaySelect();
}

typedef bool (*TableNumValidator)(size_t tableNum, _Outptr_result_maybenull_z_ TSTR* errorMsg);

static void GetValidatorAndSelectStyle(bool onlyOccupied, _Out_ TableNumValidator* validator, _Out_ ConsoleStyle* selectStyle) {
	if (!onlyOccupied) {
		*validator = &Orders_TryAssignTable;
		*selectStyle = TableOccupiedColor;
	} else {
		*validator = &Orders_IsValidAndOccupied;
		*selectStyle = TableAvailableColor;
	}
}

static bool TableSelectionOptionHandler(OptionHandlerArgs) {
	WarnIgnore_UnusedVar(navAction);
	TCHAR option = optionInput.single;
	TableSelectionInfo* selectionInfo = ((TableSelectionInfo*)extraInfo);
	AssertNotNull(selectionInfo);
	{
		BYTE tableNum;
		if (CharUtils_IsAsciiDigitOut(option, &tableNum)) {
			TableNumValidator validator;
			ConsoleStyle selectStyle;
			GetValidatorAndSelectStyle(selectionInfo->onlyOccupied, &validator, &selectStyle);
			bool valid = validator(tableNum, errorMsg);
			if (valid) {
				SelectTableInMenu(tableNum, selectStyle);
				selectionInfo->selected = tableNum;
				SleepSec(.5);
			}
			return valid;
		}
	}
	if (option == 'R') {
		selectionInfo->selected = 0;
		return true;
	}
	return false;
}

static void PrintTablesStatusPanel(bool onlyOccupied) {
	ConsoleCursor_ResetPos();
	FillLeftPanelForNewOrderMenu();
	PrintTableRow(Row1TablesPos, 1, onlyOccupied);
	PrintTableRow(Row2TablesPos, 5, onlyOccupied);
}

int TableSelection_Menu(bool onlyOccupied) {
	PrintTablesStatusPanel(onlyOccupied);
	TableSelectionInfo selectionInfo = { onlyOccupied, -1 };
	HandleOptionsExtra(&TableSelectionOptions, TableSelectionOptionHandler, &selectionInfo);
	return selectionInfo.selected;
}
