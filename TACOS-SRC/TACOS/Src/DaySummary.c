#include "DaySummary.h"
#include "StringMap.h"
#include "ConsoleOut.h"
#include "Orders.h"

static void PrintHorizontalSeparatorCustom(TCHAR startCh, TCHAR middleA, TCHAR middleB, TCHAR endCh, bool newLine) {
	ConsoleOut_WriteFormat(_T("%c%s%c%c%s%c"), startCh, SF_Repeat(L'═', 43), middleA, middleB, SF_Repeat(L'═', 43), endCh);
	if (newLine) ConsoleOut_NewLine();
}

static void PrintHorizontalSeparator2(TCHAR middleA, TCHAR middleB) {
	PrintHorizontalSeparatorCustom(L'╠', middleA, middleB, L'╣', true);
}

static void PrintHorizontalSeparator(TCHAR middle) {
	PrintHorizontalSeparator2(middle, middle);
}

static void PrintCell(TSTR content, size_t width) {
	ConsoleOut_WriteFormat(_T("║%s║"), SF_Align(content, width, ALIGN_CENTER));
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
	ConsoleOut_WriteFormat(_T("║ Opción:%s║\n"), SF_Repeat(' ', 80));
}

static void PrintTableFooter(void) {
	PrintHorizontalSeparator(L'╩');
	PrintOptionInputRow();
	PrintHorizontalSeparatorCustom(L'╚', L'═', L'═', L'╝', false);
}

#define FieldContentSize (31)

static void PrintMoneyField(TSTR fieldName, double fieldValue) {
	ConsoleOut_WriteFormat(_T("║ %s: $%s ║"),
		SF_Align(fieldName, 8, ALIGN_RIGHT),
		SF_AlignF(FieldContentSize - 1, ALIGN_LEFT, _T("%.2f"), fieldValue)
	);
}

static void PrintQuantityField(TSTR fieldName, UINT fieldValue) {
	ConsoleOut_WriteFormat(_T("║ %s: %s ║"),
		SF_Align(fieldName, 8, ALIGN_RIGHT),
		SF_AlignF(FieldContentSize, ALIGN_LEFT, _T("%d"), fieldValue)
	);
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
