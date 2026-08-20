//
// Created by XYZ on 15.11.2025.
//

#include "VariableNode.h"

using namespace std;

VariableNode::VariableNode(const string& n) {
    name = n;
}

Node* VariableNode::clone() const {
    return new VariableNode(name);
}

double VariableNode::evaluate(const double* varValues, const string* varNames, int varCount) const {
    for (int i = 0; i < varCount; i++) {
        if (varNames[i] == name) {
            return varValues[i];
        }
    }
    return 0;
}

void VariableNode::getVariables(string*& vars, int& count, int& capacity) const {
    for (int i = 0; i < count; i++) {
        if (vars[i] == name) return;
    }

    if (count >= capacity) {
        capacity = capacity * 2 + 1;
        string* newVars = new string[capacity];
        for (int i = 0; i < count; i++) {
            newVars[i] = vars[i];
        }
        delete[] vars;
        vars = newVars;
    }

    vars[count++] = name;
}

string VariableNode::toString() const {
    return name;
}

bool VariableNode::isLeaf() const {
    return true;
}

int VariableNode::getChildrenCount() const {
    return 0;
}

Node* VariableNode::getChild(int index) const {
    return NULL;
}

void VariableNode::setChild(int index, Node* child) {}