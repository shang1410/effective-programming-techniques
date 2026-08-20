#include "RefCounter.h"

RefCounter::RefCounter() {
	count = 0;
}

void RefCounter::add() {
	++count;
}

void RefCounter::dec() {
	--count;
}

int RefCounter::get() {
	return count;
}

