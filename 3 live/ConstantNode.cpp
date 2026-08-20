//
// Created by XYZ on 15.11.2025.
//

#include "ConstantNode.h"
#include <sstream>

ConstantNode::ConstantNode(double val) {
    value = val;
}

Node* ConstantNode::clone() const {
    return new ConstantNode(value);
}

double ConstantNode::evaluate(const double* varValues, const string* varNames, int varCount) const {
    return value;
}

void ConstantNode::getVariables(string*& vars, int& count, int& capacity) const {}

string ConstantNode::toString() const {
    ostringstream oss;
    oss << value;
    return oss.str();
}

bool ConstantNode::isLeaf() const {
    return true;
}

int ConstantNode::getChildrenCount() const {
    return 0;
}

Node* ConstantNode::getChild(int index) const {
    return NULL;
}

void ConstantNode::setChild(int index, Node* child) {}