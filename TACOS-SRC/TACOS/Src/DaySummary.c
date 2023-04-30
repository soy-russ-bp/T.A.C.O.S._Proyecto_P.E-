#include "DaySummary.h"
#include "StringMap.h"
#include "ConsoleOut.h"
#include "Orders.h"

static void PrintTableHeader(void) {
	ConsoleOut_WriteLine(_T("╠════════════════════════════════════════════════════════════════════════════════════════╣"));
	ConsoleOut_WriteLine(_T("║                                     Resumen del día                                    ║"));
	ConsoleOut_WriteLine(_T("╠═══════════════════════════════════════════╦╦═══════════════════════════════════════════╣"));
	ConsoleOut_WriteLine(_T("║                  Ingresos                 ║║                  Ordenes                  ║"));
	ConsoleOut_WriteLine(_T("╠═══════════════════════════════════════════╣╠═══════════════════════════════════════════╣"));
}

static void PrintTableFooter(void) {
	ConsoleOut_WriteLine(_T("╠═══════════════════════════════════════════╩╩═══════════════════════════════════════════╣"));
	ConsoleOut_WriteLine(_T("║ Opción:                                                                                ║"));
	ConsoleOut_Write/**/(_T("╚════════════════════════════════════════════════════════════════════════════════════════╝"));
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
	ConsoleOut_WriteAlignedDouble(fieldValue, FieldContentSize - 1, 15, ALIGN_LEFT);
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
