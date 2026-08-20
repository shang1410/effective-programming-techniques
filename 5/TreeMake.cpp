//
// Created by XYZ on 13.12.2025.
//

#include "TreeMake.h"


Tree createSimpleTree(OperationCounter* counter) {
    //+ 5 3
    Tree tree(counter);
    OperatorNode* plus = new OperatorNode("+");
    plus->addChild(new ConstantNode(5));
    plus->addChild(new ConstantNode(3));
    tree.setRoot(plus);
    return tree;
}

Tree createMediumTree(OperationCounter* counter) {
    //* (+ 2 3) 5
    Tree tree(counter);

    OperatorNode* plus = new OperatorNode("+");
    plus->addChild(new ConstantNode(2));
    plus->addChild(new ConstantNode(3));

    OperatorNode* mult = new OperatorNode("*");
    mult->addChild(plus);
    mult->addChild(new ConstantNode(5));

    tree.setRoot(mult);
    return tree;
}

Tree createComplexTree(OperationCounter* counter) {
    //+ (* 2 3) (* 4 5)
    Tree tree(counter);

    OperatorNode* mult1 = new OperatorNode("*");
    mult1->addChild(new ConstantNode(2));
    mult1->addChild(new ConstantNode(3));

    OperatorNode* mult2 = new OperatorNode("*");
    mult2->addChild(new ConstantNode(4));
    mult2->addChild(new ConstantNode(5));

    OperatorNode* plus = new OperatorNode("+");
    plus->addChild(mult1);
    plus->addChild(mult2);

    tree.setRoot(plus);
    return tree;
}

Tree createTreeWithVariables(OperationCounter* counter) {
    //+ (* x 2) y
    Tree tree(counter);

    OperatorNode* mult = new OperatorNode("*");
    mult->addChild(new VariableNode("x"));
    mult->addChild(new ConstantNode(2));

    OperatorNode* plus = new OperatorNode("+");
    plus->addChild(mult);
    plus->addChild(new VariableNode("y"));

    tree.setRoot(plus);
    return tree;
}

Tree createVeryComplexTree(OperationCounter* counter) {
    //+ (+ (* a 2) (* b 3)) (+ (* c 4) (* d 5))
    Tree tree(counter);

    //+ (* a 2) (* b 3)
    OperatorNode* mult1 = new OperatorNode("*");
    mult1->addChild(new VariableNode("a"));
    mult1->addChild(new ConstantNode(2));

    OperatorNode* mult2 = new OperatorNode("*");
    mult2->addChild(new VariableNode("b"));
    mult2->addChild(new ConstantNode(3));

    OperatorNode* plus1 = new OperatorNode("+");
    plus1->addChild(mult1);
    plus1->addChild(mult2);

    //+ (* c 4) (* d 5)
    OperatorNode* mult3 = new OperatorNode("*");
    mult3->addChild(new VariableNode("c"));
    mult3->addChild(new ConstantNode(4));

    OperatorNode* mult4 = new OperatorNode("*");
    mult4->addChild(new VariableNode("d"));
    mult4->addChild(new ConstantNode(5));

    OperatorNode* plus2 = new OperatorNode("+");
    plus2->addChild(mult3);
    plus2->addChild(mult4);

    //+
    OperatorNode* mainPlus = new OperatorNode("+");
    mainPlus->addChild(plus1);
    mainPlus->addChild(plus2);

    tree.setRoot(mainPlus);
    return tree;
}

