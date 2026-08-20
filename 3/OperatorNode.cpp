//
// Created by XYZ on 15.11.2025.
//

#include "OperatorNode.h"
#include <cmath>

using namespace std;

OperatorNode::OperatorNode(const string& operation) {
    op = operation;
    children = NULL;
    childrenCount = 0;

    if (op == "+" || op == "-" || op == "*" || op == "/") {
        requiredArgs = 2;
    } else if (op == "sin" || op == "cos") {
        requiredArgs = 1;
    } else {
        requiredArgs = 0;
    }

    if (requiredArgs > 0) {
        children = new Node*[requiredArgs];
        for (int i = 0; i < requiredArgs; i++) {
            *(children+i) = NULL;
        }
    }
}

OperatorNode::~OperatorNode() {
    if (children != NULL) {
        for (int i = 0; i < childrenCount; i++) {
            delete children[i];
        }
        delete[] children;
    }
}

Node* OperatorNode::clone() const {
    OperatorNode* newNode = new OperatorNode(op);
    for (int i = 0; i < childrenCount; i++) {
        newNode->addChild(children[i]->clone());
    }
    return newNode;
}

void OperatorNode::addChild(Node* child) {
    if (childrenCount < requiredArgs) {
        children[childrenCount++] = child;
    }
}

int OperatorNode::getRequiredArgs() const {
    return requiredArgs;
}

double OperatorNode::evaluate(const double* varValues, const string* varNames, int varCount) const {
    if (op == "+") {
        return children[0]->evaluate(varValues, varNames, varCount) + children[1]->evaluate(varValues, varNames, varCount);
    }

    else if (op == "-") {
        return children[0]->evaluate(varValues, varNames, varCount) - children[1]->evaluate(varValues, varNames, varCount);
    }

    else if (op == "*") {
        return children[0]->evaluate(varValues, varNames, varCount) * children[1]->evaluate(varValues, varNames, varCount);
    }

    else if (op == "/") {
        double divisor = children[1]->evaluate(varValues, varNames, varCount);

        if (divisor == 0) return 0;

        return children[0]->evaluate(varValues, varNames, varCount) / divisor;
    }

    else if (op == "sin") {
        return sin(children[0]->evaluate(varValues, varNames, varCount));
    }

    else if (op == "cos") {
        return cos(children[0]->evaluate(varValues, varNames, varCount));
    }

    return 0;
}

void OperatorNode::getVariables(string*& vars, int& count, int& capacity) const {
    for (int i = 0; i < childrenCount; i++) {
        children[i]->getVariables(vars, count, capacity);
    }
}

string OperatorNode::toString() const {
    string result = op;
    for (int i = 0; i < childrenCount; i++) {
        result += " " + children[i]->toString();
    }
    return result;
}

bool OperatorNode::isLeaf() const {
    return false;
}

int OperatorNode::getChildrenCount() const {
    return childrenCount;
}

Node* OperatorNode::getChild(int index) const {
    if (index >= 0 && index < childrenCount) {
        return children[index];
    }
    return NULL;
}

void OperatorNode::setChild(int index, Node* child) {
    if (index >= 0 && index < childrenCount) {
        delete children[index];
        children[index] = child;
    }
}