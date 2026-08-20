//
// Created by XYZ on 20.10.2025.
//

#include "ArraysServicement.h"
#include "Constans.h"
#include <iostream>

void allocTableFill34(int size) {
    if (size<=0) {
        std::cout << "Nieprawidlowa wielkosc tablicy";
        return;
    }

    int *table;
    table = new int[size];

    for (int i = 0; i < size; i++) {
        table[i] = MAGIC_NUMBER;
    }

    for (int j = 0; j < size; j++) {
        std::cout << table[j] << " ";
    }

    delete[] table;
}

bool bAllocTable2Dim(int ***piTable, int iSizeX, int iSizeY) {
    if (iSizeX <= 0 || iSizeY <= 0) {
        return false;
    }

    *piTable = new int*[iSizeX];

    for (int i = 0; i < iSizeX; i++) {
        (*piTable)[i] = new int[iSizeY];
    }
    return true;

}

bool bDeallocTable2Dim(int ***piTable, int iSizeX, int iSizeY) {
    if (iSizeX <= 0 || iSizeY <= 0 || piTable == 0) {
        return false;
    }

    for (int i = 0; i < iSizeX; i++) {
        delete[] (*piTable)[i];
    }
    delete[] *piTable;

    return true;
}