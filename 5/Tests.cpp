//
// Created by XYZ on 13.12.2025.
//

#include "Tests.h"

void test2_CopyAssignment(OperationCounter& counter) {
    cout << "\n" << endl;
    cout << "TEST 2: Przypisanie kopiujace" << endl;

    counter.reset();
    Tree t1 = createSimpleTree(&counter);
    Tree t2(&counter);

    cout << "\nt2 = t1 (kopiowanie)" << endl;
    t2 = t1;

    cout << "t1: " << t1.toString() << endl;
    cout << "t2: " << t2.toString() << endl;
    counter.print("TEST 2 - Przypisanie kopiujace");
}

void test3_MoveAssignment(OperationCounter& counter) {
    cout << "\n" << endl;
    cout << "TEST 3: Przypisanie przenoszące (std::move)" << endl;

    counter.reset();
    Tree t1 = createSimpleTree(&counter);
    Tree t2(&counter);

    cout << "\nt2 = std::move(t1) (przenoszenie)" << endl;
    t2 = std::move(t1);

    cout << "t1 po move: " << t1.toString() << " (pusty)" << endl;
    cout << "t2 po move: " << t2.toString() << endl;
    counter.print("TEST 3 - Przypisanie przenoszące");
}

void test4_OperatorPlus_WithoutMove(OperationCounter& counter) {
    cout << "\n" << endl;
    cout << "TEST 4: Operator+ BEZ move semantics" << endl;

    counter.reset();
    Tree t1 = createSimpleTree(&counter);    // + 5 3
    Tree t2 = createMediumTree(&counter);    // * (+ 2 3) 5

    cout << "\nt1: " << t1.toString() << endl;
    cout << "t2: " << t2.toString() << endl;

    cout << "\nt3 = t1 + t2" << endl;
    Tree t3 = t1 + t2;

    cout << "t3: " << t3.toString() << endl;
    counter.print("TEST 4 - Operator+ (bez optymalizacji)");
}

void test5_ChainedOperations(OperationCounter& counter) {
    cout << "\n" << endl;
    cout << "TEST 5: Łańcuch operacji (t1 + t2 + t3)" << endl;

    counter.reset();
    Tree t1 = createSimpleTree(&counter);
    Tree t2 = createSimpleTree(&counter);
    Tree t3 = createSimpleTree(&counter);

    cout << "\nresult = t1 + t2 + t3" << endl;
    Tree result = t1 + t2 + t3;

    cout << "Wynik: " << result.toString() << endl;
    counter.print("TEST 5 - Operacja lancuchowa");
}

void test6_ComplexTreeCopy(OperationCounter& counter) {
    cout << "\n" << endl;
    cout << "TEST 6: Kopiowanie złozonego drzewa" << endl;

    counter.reset();
    Tree t1 = createComplexTree(&counter);
    cout << "Utworzono złozone drzewo: " << t1.toString() << endl;

    cout << "\nKt2 = t1" << endl;
    Tree t2 = t1;

    cout << "t2: " << t2.toString() << endl;
    counter.print("TEST 6 - Kopiowanie duzego drzewa");
}

void test7_ComplexTreeMove(OperationCounter& counter) {
    cout << "\n" << endl;
    cout << "TEST 7: Przenoszenie złożonego drzewa" << endl;

    counter.reset();
    Tree t1 = createComplexTree(&counter);
    cout << "Utworzono drzewo: " << t1.toString() << endl;

    cout << "\nPrzenoszenie: t2 = std::move(t1)" << endl;
    Tree t2 = move(t1);

    cout << "t2: " << t2.toString() << endl;
    counter.print("TEST 7 - Przenoszenie duzego drzewa");
}

void test8_TreeWithVariables(OperationCounter& counter) {
    cout << "\n" << endl;
    cout << "TEST 8: Drzewo ze zmiennymi (VariableNode)" << endl;

    counter.reset();
    Tree t1 = createTreeWithVariables(&counter);
    cout << "Utworzono drzewo ze zmiennymi: " << t1.toString() << endl;

    cout << "\nKopiowanie drzewa ze zmiennymi" << endl;
    Tree t2 = t1;
    cout << "t2: " << t2.toString() << endl;

    counter.print("TEST 8 - Kopiowanie drzewa ze zmiennymi");
}

void test9_VeryComplexTree(OperationCounter& counter) {
    cout << "\n" << endl;
    cout << "TEST 9: Drzewo (13 wezlow)" << endl;

    counter.reset();
    Tree t1 = createVeryComplexTree(&counter);
    cout << "Zlozone drzewo:" << endl;
    cout << t1.toString() << endl;

    cout << "\n--- Kopiowanie ---" << endl;
    counter.reset();
    Tree t2 = t1;
    cout << "t2: " << t2.toString() << endl;
    counter.print("Kopiowanie 13-wezlowego drzewa");

    cout << "\n--- Przenoszenie ---" << endl;
    counter.reset();
    Tree t3 = createVeryComplexTree(&counter);
    counter.reset();
    Tree t4 = move(t3);
    cout << "t4: " << t4.toString() << endl;
    counter.print("Przenoszenie 13-wezlowego drzewa");
}

