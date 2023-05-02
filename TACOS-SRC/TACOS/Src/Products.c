#include "Products.h"
#include "ArrayUtils.h"

static const ProductInfo Products[] = {
	{ _T("TAP"), _T("Tacos de pastor"),		15.00 },
	{ _T("TDA"), _T("Tacos de asada"),		17.50 },
	{ _T("TAB"), _T("Tacos de barbacoa"),	20.00 },
	{ _T("TBI"), _T("Tacos de birriaa"),	16.00 },
	{ _T("TEE"), _T("Té"),					12.50 },
	{ _T("HOR"), _T("Horchata"),			10.00 },
	{ _T("CEB"), _T("Cebada"),				14.50 }
};

const size_t Products_TypesCount = StaticLength(Products);

ProductInfo Products_GetProductInfo(size_t index) {
	Array_IsInBounds(index, Products_TypesCount);
	return Products[index];
}

_Success_(OnTrueReturn) bool Products_TryGetIndexByCode(SalExt_Str_In_NotNull_ TSTR code, _Out_ size_t* index) {
	for (size_t productI = 0; productI < Products_TypesCount; productI++) {
		TSTR prodCode = Products[productI].code;
		if (TStrCmp(prodCode, code) == 0) {
			*index = productI;
			return true;
		}
	}
	return false;
}
