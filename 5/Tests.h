//
// Created by XYZ on 13.12.2025.
//

#ifndef LISTA5_TESTS_H
#define LISTA5_TESTS_H

#include <iostream>
#include "Tree.h"
#include "OperationCounter.h"
#include "TreeMake.h"

using namespace std;

void test1_SimpleReturn(OperationCounter& counter);
void test2_CopyAssignment(OperationCounter& counter);
void test3_MoveAssignment(OperationCounter& counter);
void test4_OperatorPlus_WithoutMove(OperationCounter& counter);
void test5_ChainedOperations(OperationCounter& counter);
void test6_ComplexTreeCopy(OperationCounter& counter);
void test7_ComplexTreeMove(OperationCounter& counter);
void test8_TreeWithVariables(OperationCounter& counter);
void test9_VeryComplexTree(OperationCounter& counter);

#endif //LISTA5_TESTS_H