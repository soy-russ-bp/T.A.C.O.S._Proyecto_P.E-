#include "Flags.h"
#pragma once
#include "StringMap.h"
#include "Products.h"

// Elemento de una orden.
typedef struct OrderElement {
	ProductInfo product;
	size_t count;
} OrderElement;

#define GDEC
#define GTYPE OrderElement
#define GNAME Order
#include "LinkedList.h"
