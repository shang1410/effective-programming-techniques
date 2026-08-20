#include "Interface.h"
#include "Tests.h"

int main() {
    // Interface interface;
    // interface.run();
    // return 0;

    OperationCounter counter;

    test2_CopyAssignment(counter);
    test3_MoveAssignment(counter);
    test4_OperatorPlus_WithoutMove(counter);
    test5_ChainedOperations(counter);
    test6_ComplexTreeCopy(counter);
    test7_ComplexTreeMove(counter);
    test8_TreeWithVariables(counter);
    test9_VeryComplexTree(counter);

    return 0;


}