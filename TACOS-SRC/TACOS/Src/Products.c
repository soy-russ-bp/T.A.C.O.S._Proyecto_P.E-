#include "Products.h"
#include "ArrayUtils.h"

static const ProductInfo Products[] = {
	{ _T("Tacos de pastor"), 15 },
	{ _T("Tacos de asada"), 20 }
};

static const int ProductTypesCount = StaticLength(Products);

size_t Products_GetTypesCount(void) {
	return ProductTypesCount;
}

ProductInfo Products_GetProductInfo(size_t index) {
	Array_IsInBounds(index, ProductTypesCount);
	return Products[index];
}
