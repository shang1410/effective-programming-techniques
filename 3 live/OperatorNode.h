//
// Created by XYZ on 15.11.2025.
//

#ifndef LISTA_3_OPERATORNODE_H
#define LISTA_3_OPERATORNODE_H

#include "Node.h"

using namespace std;

class OperatorNode: public Node {
    private:
        string op;
        Node** children;
        int childrenCount;
        int requiredArgs;

    public:
        OperatorNode(const string& operation);
        ~OperatorNode();
        Node* clone() const;
        void addChild(Node* child);
        int getRequiredArgs() const;
        double evaluate(const double* varValues, const string* varNames, int varCount) const;
        void getVariables(string*& vars, int& count, int& capacity) const;
        string toString() const;
        bool isLeaf() const;
        int getChildrenCount() const;
        Node* getChild(int index) const;
        void setChild(int index, Node* child);
};


#endif //LISTA_3_OPERATORNODE_H