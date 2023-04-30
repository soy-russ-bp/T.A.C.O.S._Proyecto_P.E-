#include "Flags.h"
#pragma once
#include "StringMap.h"

// Info de un producto del restaurante.
typedef struct ProductInfo {
	const TSTR code;
	const TSTR name;
	const double price;
} ProductInfo;

extern const size_t Products_TypesCount;

ProductInfo Products_GetProductInfo(size_t index);
