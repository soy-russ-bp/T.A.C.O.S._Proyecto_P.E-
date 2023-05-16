#include "TextLayout.h"
#include "Exceptions.h"
#include "MathUtils.h"

static void CheckForOverflow(size_t textLength, size_t width) {
	Assert(textLength <= width, "The length of the text exceeds the width");
}

static void TextLayout_PartialLeftPaddingInfo(size_t textLength, size_t width, _Out_ size_t* dif, _Out_ size_t* leftPad) {
	CheckForOverflow(textLength, width);
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

static size_t GetSidePadding(size_t textLength, size_t width) {
	CheckForOverflow(textLength, width);
	return width - textLength;
}

void TextLayout_AlignedTextPadding(size_t textLength, size_t width, TextAlignment alignment, _Out_ size_t* leftPad, _Out_ size_t* rightPad) {
	switch (alignment) {
		case ALIGN_LEFT:
			*leftPad = 0;
			*rightPad = GetSidePadding(textLength, width);
			break;
		case ALIGN_CENTER:
			TextLayout_CenterTextPadding(textLength, width, leftPad, rightPad);
			break;
		case ALIGN_RIGHT:
			*leftPad = GetSidePadding(textLength, width);
			*rightPad = 0;
			break;
		default:
			Throw("Invalid alignment");
	}
}
