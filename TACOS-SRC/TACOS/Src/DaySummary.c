#include "DaySummary.h"
#include "StringMap.h"
#include "ConsoleOut.h"

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

static void PrintTableField(TSTR fieldName, UINT value) {
	ConsoleOut_Write(_T("║ "));
	ConsoleOut_WriteAligned(fieldName, 8, ALIGN_RIGHT);
	ConsoleOut_Write(_T(": $"));
	//ConsoleOut_Write(_T("║ "));
	ConsoleOut_WriteChar(L'║');
}

static void PrintTableFieldRow(TSTR field1Name, UINT value1, TSTR field2Name, UINT value2) {
	PrintTableField(field1Name, value1);
	PrintTableField(field2Name, value2);
	ConsoleOut_NewLine();
}

static void PrintTableData(void) {
	// TODO
	// PrintTableFieldRow(_T("Subtotal"), 0, _T("Abiertas"), 0);
	// PrintTableFieldRow(_T("Propina"), 0, _T("Cerradas"), 0);
	// PrintTableFieldRow(_T("Total"), 0, _T("Totales"), 0);
	ConsoleOut_WriteLine(_T("║ Subtotal: $0                              ║║ Abiertas: 0                               ║"));
	ConsoleOut_WriteLine(_T("║  Propina: $0                              ║║ Cerradas: 0                               ║"));
	ConsoleOut_WriteLine(_T("║    Total: $0                              ║║  Totales: 0                               ║"));
}

void DaySummary_PrintTable(void) {
	PrintTableHeader();
	PrintTableData();
	PrintTableFooter();
}
