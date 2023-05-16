#include "Flags.h"
#pragma once
#include "StringMap.h"
#include "WarnIgnore.h"

WarnIgnore_AddedPadding_S
// Info de un producto del restaurante.
typedef struct ProductInfo {
	const TSTR code;
	const TSTR name;
	const double price;
	const bool isDrink;
} ProductInfo;
WarnIgnore_AddedPadding_E

extern const size_t Products_TypesCount;

const ProductInfo* Products_GetProductInfo(size_t index);

_Success_(OnTrueReturn) bool Products_TryGetByCode(SalExt_Str_In_NotNull_ TSTR code, _Out_opt_ size_t* index, _Outptr_ const ProductInfo** productInfo);
