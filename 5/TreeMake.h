//
// Created by XYZ on 13.12.2025.
//

#ifndef LISTA5_TREEMAKE_H
#define LISTA5_TREEMAKE_H

#include "Tree.h"
#include "OperationCounter.h"
#include "VariableNode.h"
#include "ConstantNode.h"
#include "OperatorNode.h"


Tree createSimpleTree(OperationCounter* counter);
Tree createMediumTree(OperationCounter* counter);
Tree createComplexTree(OperationCounter* counter);
Tree createTreeWithVariables(OperationCounter* counter);
Tree createVeryComplexTree(OperationCounter* counter);


#endif //LISTA5_TREEMAKE_H