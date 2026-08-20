#include <iostream>

#include "ArraysFunctions.h"



int main() {
    int **table;
    int rows=2, cols=3;

    if (allocate_flat_table(&table, rows, cols)) {
        std::cout << "Udalo się" << std::endl;
    };

    fill_consecutive_numbers(&table, rows, cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << table[i][j] << std::endl;
        }
    }

    deallocate_flat_table(&table, rows, cols);

}