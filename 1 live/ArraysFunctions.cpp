//
// Created by XYZ on 22.10.2025.
//

#include "ArraysFunctions.h"
#include <iostream>

bool allocate_flat_table(int ***table, int rows, int cols) {
    if (rows <= 0 || cols <= 0) {
        return false;
    }
    int len = rows * cols;

    int* flatArray;
    flatArray = new int[len];

    int** rowPointers;
    rowPointers = new int*[rows];

    for (int i = 0; i < rows; i++) {
        rowPointers[i] = &flatArray[i * cols];
        //*rowPointers
    }

    *table = rowPointers;

    return true;
}


void fill_consecutive_numbers(int ***table, int rows, int cols) {
    if (rows <= 1 || cols <= 0) {
        std::cout << "Bledne parametry" << std::endl;
        return;
    }

    int k=1;
    for (int i = 0; i < rows; i++) {
        for (int j=0; j<cols; j++) {
            (*table)[i][j] = k;
            k++;
        }
    }

}


bool deallocate_flat_table(int ***table, int rows, int cols) {
    if (table == NULL || *table == NULL || rows <= 0 || cols <= 0) {
        std::cout << "Bledne parametry" << std::endl;
        return false;
    }

    int* flatArray = (*table)[0];

    delete[] flatArray;
    delete[] *table;

    *table = NULL;

    return true;
}
