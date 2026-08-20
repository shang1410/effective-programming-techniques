#include <iostream>
#include "ArraysServicement.h"
#include "CTable.h"
#include "Constans.h"

int main() {
    allocTableFill34(FILL_SIZE);
    std::cout << "\n";

    int **table2D;

    if (bAllocTable2Dim(&table2D, ROWS, COLS)) {
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                table2D[i][j] = i+j;
                std::cout << table2D[i][j] << " ";
            }
            std::cout << "\n";
        }
    }

    if (bDeallocTable2Dim(&table2D, ROWS, COLS)) {
        std::cout << "Pomyslnie skasowano\n\n";
    }

    std::cout << "Konstruktory\n";
    CTable tab1;
    CTable tab2("Tablica2", 5);
    CTable tab3(tab2);

    std::cout << "\nMetody\n";
    tab1.vSetName("Tablica1");
    tab1.vPrint();
    tab2.vPrint();
    tab3.vPrint();

    std::cout << "\nZmiana rozmiaru\n";
    tab1.bSetNewSize(10);
    tab1.vPrint();

    std::cout << "\nKlonowanie\n";
    CTable *clonedTab = tab2.pcClone();
    clonedTab->vPrint();

    std::cout << "\nProcedury v_mod_tab\n";
    std::cout << "Przed v_mod_tab (przez wskaznik): ";
    tab2.vPrint();
    vModTab(&tab2, 8);
    std::cout << "Po v_mod_tab (przez wskaznik): ";
    tab2.vPrint();

    std::cout << "Przed v_mod_tab (przez wartosc): ";
    tab3.vPrint();
    vModTab(tab3, 12);
    std::cout << "Po v_mod_tab (przez wartosc): ";
    tab3.vPrint();

    std::cout << "\nAlokacja statyczna i dynamiczna\n";
    CTable staticTab("StaticTab", 3);

    CTable* dynamicTab = new CTable("DynamicTab", 4);
    dynamicTab->vPrint();

    std::cout << "\nTablica obiektów ===\n";
    CTable* tabArray = new CTable[3];

    std::cout << "\nCzyszczenie pamięci ===\n";
    delete clonedTab;
    delete dynamicTab;
    delete[] tabArray;

    return 0;
}
