//
// Created by XYZ on 15.11.2025.
//

#include "ValueList.h"

using namespace std;

ValueList::ValueList() {
    values = 0;
    count = 0;
    capacity = 0;
}

ValueList::~ValueList() {
    delete[] values;
}

void ValueList::add(double value) {
    if (count >= capacity) {
        capacity = capacity * 2 + 1;
        double* newValues = new double[capacity];
        for (int i = 0; i < count; i++) {
            newValues[i] = values[i];
        }
        delete[] values;
        values = newValues;
    }
    values[count++] = value;
}

int ValueList::getCount() const {
    return count;
}

const double* ValueList::getValues() const {
    return values;
}