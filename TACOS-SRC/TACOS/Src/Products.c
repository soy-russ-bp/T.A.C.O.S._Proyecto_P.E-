#include "Products.h"
#include "ArrayUtils.h"

static const ProductInfo Products[] = {
	{ _T("Tacos de pastor"), 15 },
	{ _T("Tacos de asada"), 20 }
};

const size_t Products_TypesCount = StaticLength(Products);

ProductInfo Products_GetProductInfo(size_t index) {
	Array_IsInBounds(index, Products_TypesCount);
	return Products[index];
}
