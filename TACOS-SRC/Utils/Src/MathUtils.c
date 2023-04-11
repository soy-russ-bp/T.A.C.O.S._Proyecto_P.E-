#include "MathUtils.h"

bool Math_IsInURange(UINT num, UINT min, UINT max) {
	return ((num - min) <= (max - min));
}

bool Math_IsEven(int num) {
	return num % 2 == 0;
}

size_t Math_DigitCount(int num) {
	size_t count = 0;
	while (num != 0) {
		num /= 10;
		count++;
	}
	return count;
}
