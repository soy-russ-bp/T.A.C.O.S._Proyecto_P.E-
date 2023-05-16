#include "Flags.h"
#pragma once

typedef enum TextAlignment {
    ALIGN_LEFT,
    ALIGN_CENTER,
    ALIGN_RIGHT
} TextAlignment;

size_t TextLayout_CenterTextLeftPadding(size_t textLength, size_t width);

void TextLayout_CenterTextPadding(size_t textLength, size_t width, _Out_ size_t* leftPad, _Out_ size_t* rightPad);

void TextLayout_AlignedTextPadding(size_t textLength, size_t width, TextAlignment alignment, _Out_ size_t* leftPad, _Out_ size_t* rightPad);
