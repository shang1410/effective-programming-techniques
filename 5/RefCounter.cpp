//
// Created by XYZ on 13.12.2025.
//

#include "RefCounter.h"

RefCounter::RefCounter() {
    count = 0;
}

int RefCounter::add() {
    return(++count);
}

int RefCounter::dec() {
    return(--count);
}

int RefCounter::get() {
    return(count);
}