#include "Products.h"
#include "ArrayUtils.h"

static const ProductInfo Products[] = {
	{ _T("TAP"), _T("Tacos de pastor"),		15.00, false },
	{ _T("TDA"), _T("Tacos de asada"),		17.50, false },
	{ _T("TAB"), _T("Tacos de barbacoa"),	20.00, false },
	{ _T("TBI"), _T("Tacos de birriaa"),	16.00, false },
	{ _T("TEE"), _T("Té"),					12.50, true  },
	{ _T("HOR"), _T("Horchata"),			10.00, true  },
	{ _T("CEB"), _T("Cebada"),				14.50, true  }
};

const size_t Products_TypesCount = StaticLength(Products);

const ProductInfo* Products_GetProductInfo(size_t index) {
	Array_IsInBounds(index, Products_TypesCount);
	return &Products[index];
}

_Success_(OnTrueReturn) bool Products_TryGetByCode(SalExt_Str_In_NotNull_ TSTR code, _Out_opt_ size_t* index, _Outptr_ const ProductInfo** productInfo) {
	for (size_t productI = 0; productI < Products_TypesCount; productI++) {
		const ProductInfo* product = &Products[productI];
		if (TStrCmp(code, product->code) == 0) {
			if (index != NULL) *index = productI;
			*productInfo = product;
			return true;
		}
	}
	return false;
}
