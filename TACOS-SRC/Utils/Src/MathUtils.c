#include "MathUtils.h"

bool Math_IsInURange(UINT num, UINT min, UINT max) {
	return ((num - min) <= (max - min));
}

bool Math_IsEven(int num) {
	return num % 2 == 0;
}

size_t Math_DigitCount(int num) {
	if (num == 0) return 1;
	size_t count = 0;
	do {
		num /= 10;
		count++;
	} while (num != 0);
	return count;
}
