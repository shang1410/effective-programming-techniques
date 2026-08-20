//
// Created by XYZ on 15.11.2025.
//

#ifndef LISTA_3_VARIABLENODE_H
#define LISTA_3_VARIABLENODE_H

#include "Node.h"

class VariableNode : public Node {
    private:
        string name;

    public:
        VariableNode(const string& n);
        Node* clone() const;
        double evaluate(const double* varValues, const string* varNames, int varCount) const;
        void getVariables(string*& vars, int& count, int& capacity) const;
        string toString() const;
        bool isLeaf() const;
        int getChildrenCount() const;
        Node* getChild(int index) const;
        void setChild(int index, Node* child);
};


#endif //LISTA_3_VARIABLENODE_H