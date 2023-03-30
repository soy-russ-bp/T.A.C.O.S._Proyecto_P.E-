#include "TextLayout.h"
#include "Exceptions.h"
#include "MathUtils.h"

static void TextLayout_PartialLeftPaddingInfo(size_t textLength, size_t width, _Out_ size_t* dif, _Out_ size_t* leftPad) {
	Assert(textLength <= width, "The length of the text exceeds the width.");
	*dif = width - textLength;
	*leftPad = *dif / 2;
}

static void TextLayout_AddFinalOffsetToLeftPadding(size_t dif, _Inout_ size_t* leftPad) {
	if (!Math_IsEven((int)dif)) {
		(*leftPad)++;
	}
}

size_t TextLayout_CenterTextLeftPadding(size_t textLength, size_t width) {
	size_t dif, leftPad;
	TextLayout_PartialLeftPaddingInfo(textLength, width, &dif, &leftPad);
	TextLayout_AddFinalOffsetToLeftPadding(dif, &leftPad);
	return leftPad;
}

void TextLayout_CenterTextPadding(size_t textLength, size_t width, _Out_ size_t* leftPad, _Out_ size_t* rightPad) {
	size_t dif;
	TextLayout_PartialLeftPaddingInfo(textLength, width, &dif, leftPad);
	*rightPad = *leftPad;
	TextLayout_AddFinalOffsetToLeftPadding(dif, leftPad);
}
