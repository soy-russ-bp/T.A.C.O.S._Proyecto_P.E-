#pragma once // NOLINT

#ifndef __clang_analyzer__
// Módulo: Flags.h
// Configuración del compilador y analizadores.
#endif

#ifdef __clang_analyzer__
#define ClangDiagnostic(exp) __pragma(clang diagnostic exp)
#else
#define ClangDiagnostic(exp)
#endif

ClangDiagnostic(ignored "-Wpragma-once-outside-header")
ClangDiagnostic(ignored "-Wempty-translation-unit")
ClangDiagnostic(ignored "-Wdeclaration-after-statement")
ClangDiagnostic(ignored "-Wunused-parameter")
ClangDiagnostic(ignored "-Wunused-macros")
ClangDiagnostic(ignored "-Wswitch-enum")
ClangDiagnostic(ignored "-Wcovered-switch-default")
ClangDiagnostic(ignored "-Winvalid-utf8")

#ifdef _MSC_VER
#pragma warning( disable : 5045 ) // Compiler will insert Spectre mitigation for memory load if /Qspectre switch specified
#pragma warning( disable : 4061 ) // Enumerator 'identifier' in switch of enum 'enumeration' is not explicitly handled by a case label
#else
#error Compatible únicamente con MSVC
#endif

#include "SysArch.h"
#include "GlobalDefines.h"

#ifdef WidePrint
#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif
#else
#undef UNICODE
#undef _UNICODE // NOLINT
#endif

#include "GlobalIncludes.h"
