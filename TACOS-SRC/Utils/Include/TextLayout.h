#include "Flags.h"
#pragma once

size_t TextLayout_CenterTextLeftPadding(size_t textLength, size_t width);

void TextLayout_CenterTextPadding(size_t textLength, size_t width, _Out_ size_t* leftPad, _Out_ size_t* rightPad);
