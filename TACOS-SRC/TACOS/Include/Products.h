#include "Flags.h"
#pragma once
#include "StringMap.h"
#include "WarnIgnore.h"

WarnIgnore_AddedPadding_S
// Info de un producto del restaurante.
typedef struct ProductInfo {
	const TSTR name;
	const double price;
} ProductInfo;
WarnIgnore_AddedPadding_E

size_t Products_GetTypesCount(void);

ProductInfo Products_GetProductInfo(size_t index);
