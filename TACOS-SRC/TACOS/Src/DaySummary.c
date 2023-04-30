#include "DaySummary.h"
#include "StringMap.h"
#include "ConsoleOut.h"
#include "Orders.h"

static void PrintHorizontalSeparatorCustom(TCHAR startCh, TCHAR middleA, TCHAR middleB, TCHAR endCh, bool newLine) {
	ConsoleOut_WriteChar(startCh);
	ConsoleOut_WriteCharRepeat(L'═', 43);
	ConsoleOut_WriteChar(middleA);
	ConsoleOut_WriteChar(middleB);
	ConsoleOut_WriteCharRepeat(L'═', 43);
	ConsoleOut_WriteChar(endCh);
	if (newLine) {
		ConsoleOut_NewLine();
	}
}

static void PrintHorizontalSeparator2(TCHAR middleA, TCHAR middleB) {
	PrintHorizontalSeparatorCustom(L'╠', middleA, middleB, L'╣', true);
}

static void PrintHorizontalSeparator(TCHAR middle) {
	PrintHorizontalSeparatorCustom(L'╠', middle, middle, L'╣', true);
}

static void PrintCell(TSTR content, size_t width) {
	ConsoleOut_WriteChar(L'║');
	ConsoleOut_WriteAligned(content, width, ALIGN_CENTER);
	ConsoleOut_WriteChar(L'║');
}

static void PrintTableHeader(void) {
	PrintHorizontalSeparator(L'═');
	PrintCell(_T("Resumen del día"), 88);
	ConsoleOut_NewLine();
	PrintHorizontalSeparator(L'╦');
	PrintCell(_T("Ingresos"), 43);
	PrintCell(_T("Ordenes"), 43);
	ConsoleOut_NewLine();
	PrintHorizontalSeparator2(L'╣', L'╠');
}

static void PrintOptionInputRow(void) {
	ConsoleOut_Write(_T("║ Opción:"));
	ConsoleOut_WriteCharRepeat(' ', 80);
	ConsoleOut_WriteChar(L'║');
	ConsoleOut_NewLine();
}

static void PrintTableFooter(void) {
	PrintHorizontalSeparator(L'╩');
	PrintOptionInputRow();
	PrintHorizontalSeparatorCustom(L'╚', L'═', L'═', L'╝', false);
}

static void PrintFieldStart(TSTR fieldName) {
	ConsoleOut_Write(_T("║ "));
	ConsoleOut_WriteAligned(fieldName, 8, ALIGN_RIGHT);
	ConsoleOut_Write(_T(": "));
}

static void PrintFieldEnd(void) {
	ConsoleOut_Write(_T(" ║"));
}

#define FieldContentSize (31)

static void PrintMoneyField(TSTR fieldName, double fieldValue) {
	PrintFieldStart(fieldName);
	ConsoleOut_WriteChar(L'$');
	ConsoleOut_WriteAlignedDouble(fieldValue, FieldContentSize - 1, 2, ALIGN_LEFT);
	PrintFieldEnd();
}

static void PrintQuantityField(TSTR fieldName, UINT fieldValue) {
	PrintFieldStart(fieldName);
	ConsoleOut_WriteAlignedUInt(fieldValue, FieldContentSize, ALIGN_LEFT);
	PrintFieldEnd();
}

static void PrintFieldRow(TSTR moneyFieldName, double moneyFieldValue, TSTR quantityFieldName, UINT quantityFieldValue) {
	PrintMoneyField(moneyFieldName, moneyFieldValue);
	PrintQuantityField(quantityFieldName, quantityFieldValue);
	ConsoleOut_NewLine();
}

static void PrintRow1(void) {
	UINT openCount = Orders_GetOpenCount();
	PrintFieldRow(_T("Subtotal"), 0, _T("Abiertas"), openCount);
}

static void PrintRow2(void) {
	PrintFieldRow(_T("Propina"), 0, _T("Cerradas"), 0);
}

static void PrintRow3(void) {
	PrintFieldRow(_T("Total"), 0, _T("Totales"), 0);
}

static void PrintTableData(void) {
	PrintRow1();
	PrintRow2();
	PrintRow3();
}

void DaySummary_PrintTable(void) {
	PrintTableHeader();
	PrintTableData();
	PrintTableFooter();
}
