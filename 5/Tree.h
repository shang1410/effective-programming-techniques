//
// Created by XYZ on 15.11.2025.
//

#ifndef LISTA_3_TREE_H
#define LISTA_3_TREE_H

#include "Node.h"
#include "TokenList.h"
#include "Result.h"
#include "Error.h"
#include <string>
#include <vector>

using namespace std;

class Tree {
private:
    Node* root;
    OperationCounter* counterTree;

    bool isOperator(const string& s) const;
    bool isNumber(const string& s) const;
    bool isVariable(const string& s) const;
    string cleanToken(const string& token) const;

    Node* buildTree(const TokenList& tokens, int& index, vector<Error*>& errors);
    void findFirstLeaf(Node* node, Node*& leafParent, int& leafIndex);
    void setCounterForTree(Node *node);

public:
    Tree();

    Tree(OperationCounter *cnt);

    Tree(const Tree& other);
    Tree(Tree &&other);

    ~Tree();

    Tree operator=(const Tree& other);
    //Tree& operator=(const Tree& other);

    Tree &operator=(Tree &&other);

    Tree operator+(const Tree& other) const;

    Result<Tree, Error> enter(const string& formula);

    string toString() const;
    void print() const;
    void getVars(string*& vars, int& count) const;
    void printVars() const;
    bool compute(const double* values, int valueCount) const;

    int altitude(Node* root) const;
    string draw() const;

    void setRoot(Node *node);

    void setCounter(OperationCounter *cnt);

    Node* getRoot() const { return root; }
};

#endif //LISTA_3_TREE_H