//
// Created by XYZ on 15.11.2025.
//

#ifndef LISTA_3_TREE_H
#define LISTA_3_TREE_H

#include "Node.h"
#include "TokenList.h"
#include <string>

using namespace std;

class Tree {
    private:
        Node* root;

        bool isOperator(const string& s) const;
        bool isNumber(const string& s) const;
        bool isVariable(const string& s) const;
        string cleanToken(const string& token) const;
        Node* buildTree(const TokenList& tokens, int& index, bool& modified);
        void findFirstLeaf(Node* node, Node*& leafParent, int& leafIndex);
        int altitude(Node *root) const;

    public:
        Tree();
        Tree(const Tree& other);
        ~Tree();
        Tree& operator=(const Tree& other);
        Tree operator+(const Tree& other) const;
        bool enter(const string& formula);
        string toString() const;
        void print() const;
        void getVars(string*& vars, int& count) const;
        void printVars() const;
        bool compute(const double* values, int valueCount) const;

        string draw() const;
};


#endif //LISTA_3_TREE_H