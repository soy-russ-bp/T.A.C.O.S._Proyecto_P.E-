#pragma once // NOLINT
#include "SysArch.h"

#ifndef __clang_analyzer__
// Módulo: Flags.h
// Configuración del compilador y analizadores.
#endif

#ifdef __clang_analyzer__
#pragma clang diagnostic ignored "-Wpragma-once-outside-header"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wdeclaration-after-statement"
#pragma clang diagnostic ignored "-Wunused-parameter"
#pragma clang diagnostic ignored "-Wunused-macros"
#pragma clang diagnostic ignored "-Wswitch-enum"
#pragma clang diagnostic ignored "-Wcovered-switch-default"
#pragma clang diagnostic ignored "-Winvalid-utf8"
#endif

#ifdef _MSC_VER
#pragma warning( disable : 5045 ) // Compiler will insert Spectre mitigation for memory load if /Qspectre switch specified
#pragma warning( disable : 4061 ) // Enumerator 'identifier' in switch of enum 'enumeration' is not explicitly handled by a case label
#else
#error Compatible únicamente con MSVC
#endif

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
