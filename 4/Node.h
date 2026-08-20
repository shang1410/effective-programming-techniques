//
// Created by XYZ on 15.11.2025.
//

#ifndef LISTA_3_NODE_H
#define LISTA_3_NODE_H
#include <string>

using namespace std;


class Node {
    public:
        virtual ~Node() {}
        virtual Node* clone() const = 0;
        virtual double evaluate(const double* varValues, const string* varNames, int varCount) const = 0;
        virtual void getVariables(string*& vars, int& count, int& capacity) const = 0;
        virtual string toString() const = 0;
        virtual bool isLeaf() const = 0;
        virtual int getChildrenCount() const = 0;
        virtual Node* getChild(int index) const = 0;
        virtual void setChild(int index, Node* child) = 0;
};

#endif //LISTA_3_NODE_H