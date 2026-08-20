//
// Created by XYZ on 15.11.2025.
//

#include "Tree.h"
#include "ConstantNode.h"
#include "VariableNode.h"
#include "OperatorNode.h"
#include <sstream>
#include <iostream>

Tree::Tree() {
    root = NULL;
}

Tree::Tree(OperationCounter* cnt) {
    root = NULL;
    counterTree=cnt;
}

Tree::Tree(const Tree& other) {
    counterTree = other.counterTree;
    if (counterTree != NULL) {
        counterTree->incrementCopyConstructor();
    }
    root = NULL;
    if (other.root != NULL) {
        root = other.root->clone();
        setCounterForTree(root);
    }
}

Tree::Tree(Tree&& other) {
    counterTree = other.counterTree;
    if (counterTree != NULL) {
        counterTree->incrementMoveConstructor();
    }
    root = other.root;
    other.root = NULL;
}

Tree::~Tree() {
    delete root;
}

// Tree& Tree::operator=(const Tree &other) {
//     if (this != &other) {
//         counterTree = other.counterTree;
//         if (counterTree != NULL) {
//             counterTree->incrementCopyAssignment();
//         }
//         delete root;
//         if (other.root != NULL) {
//             root = other.root->clone();
//             setCounterForTree(root);
//         } else {
//             root = NULL;
//         }
//     }
//     return (*this);
// }

Tree Tree::operator=(const Tree &other) {
    if (this != &other) {
        counterTree = other.counterTree;
        if (counterTree != NULL) {
            counterTree->incrementCopyAssignment();
        }
        delete root;
        if (other.root != NULL) {
            root = other.root->clone();
            setCounterForTree(root);
        } else {
            root = NULL;
        }
    }
    return *this;
}

Tree& Tree::operator=(Tree&& other) {
    if (this != &other) {
        counterTree = other.counterTree;
        if (counterTree != NULL) {
            counterTree->incrementMoveAssignment();
        }
        delete root;
        root = other.root;
        other.root = NULL;
    }
    return *this;
}


Tree Tree::operator+(const Tree& other) const {
    Tree result(*this);
    result.counterTree = counterTree;

    if (result.root == NULL) {
        result = other;
        return result;
    }

    if (other.root == NULL) {
        return result;
    }

    Node* leafParent = NULL;
    int leafIndex = -1;

    if (result.root->isLeaf()) {
        delete result.root;
        result.root = other.root->clone();
        result.setCounterForTree(result.root);
        return result;
    }

    result.findFirstLeaf(result.root, leafParent, leafIndex);

    if (leafParent != NULL && leafIndex >= 0) {
        Node* clonedNode = other.root->clone();
        clonedNode->setCounter(counterTree);
        result.setCounterForTree(clonedNode);
        leafParent->setChild(leafIndex, clonedNode);
    }

    return result;
}

void Tree::setCounterForTree(Node* node) {
    if (node == NULL) return;
    node->setCounter(counterTree);
    for (int i = 0; i < node->getChildrenCount(); i++) {
        setCounterForTree(node->getChild(i));
    }
}

bool Tree::isOperator(const string& s) const {
    return s == "+" || s == "-" || s == "*" || s == "/" ||
           s == "sin" || s == "cos";
}

bool Tree::isNumber(const std::string& s) const {
    if (s.empty()) return false;
    int start = 0;

    if (s[0] == '-') {
        if (s.length() == 1) return false;
        start = 1;
    }

    for (int i = start; i < s.length(); i++) {
        if (s[i] < '0' || s[i] > '9') return false;
    }
    return true;
}

bool Tree::isVariable(const string& s) const {
    if (s.empty()) return false;
    bool hasLetter = false;
    for (int i = 0; i < s.length(); i++) {
        char c = s[i];
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            hasLetter = true;
        } else if (c >= '0' && c <= '9') {
            continue;
        } else {
            return false;
        }
    }
    return hasLetter;
}

string Tree::cleanToken(const string& token) const {
    string cleaned;
    for (int i = 0; i < token.length(); i++) {
        char c = token[i];
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) {
            cleaned += c;
        }
    }
    return cleaned;
}

Node* Tree::buildTree(const TokenList& tokens, int& index, vector<Error*>& errors) {
    if (index >= tokens.getCount()) {
        errors.push_back(new Error("Brak wystarczajacej liczby argumentow"));
        return NULL;
    }

    string token = tokens.get(index);
    index++;

    if (isOperator(token)) {
        OperatorNode* node = new OperatorNode(token);
        int required = node->getRequiredArgs();

        for (int i = 0; i < required; i++) {
            Node* child = buildTree(tokens, index, errors);
            if (child == NULL) {
                delete node;
                return NULL;
            }
            node->addChild(child);
        }

        return node;
    }
    else if (isNumber(token)) {
        double val = 0;
        istringstream iss(token);
        iss >> val;
        return new ConstantNode(val);
    }
    else {
        string cleaned = cleanToken(token);
        if (isVariable(cleaned)) {
            return new VariableNode(cleaned);
        } else if (isNumber(cleaned)) {
            double val = 0;
            istringstream iss(cleaned);
            iss >> val;
            return new ConstantNode(val);
        }
        errors.push_back(new Error("Nieprawidlowy token: " + token));
        return NULL;
    }
}

void Tree::findFirstLeaf(Node* node, Node*& leafParent, int& leafIndex) {
    if (node == NULL) return;

    if (node->isLeaf()) {
        return;
    }

    for (int i = 0; i < node->getChildrenCount(); i++) {
        Node* child = node->getChild(i);
        if (child->isLeaf()) {
            leafParent = node;
            leafIndex = i;
            return;
        }
        findFirstLeaf(child, leafParent, leafIndex);
        if (leafParent != NULL) return;
    }
}

Result<Tree, Error> Tree::enter(const string& formula) {
    TokenList tokens;
    istringstream iss(formula);
    string token;

    while (iss >> token) {
        tokens.add(token);
    }

    if (tokens.getCount() == 0) {
        return Result<Tree, Error>::failClass(
            new Error("Puste wyrazenie")
        );
    }

    int index = 0;
    vector<Error*> errors;
    Node* newRoot = buildTree(tokens, index, errors);

    if (!errors.empty()) {
        delete newRoot;
        return Result<Tree, Error>::failClass(errors);
    }

    if (newRoot == NULL) {
        return Result<Tree, Error>::failClass(
            new Error("Nie udalo sie zbudowac drzewa")
        );
    }

    if (index < tokens.getCount()) {
        delete newRoot;
        return Result<Tree, Error>::failClass(
            new Error("Nadmiarowe symbole w wyrazeniu")
        );
    }

    Tree newTree;
    newTree.root = newRoot;

    return Result<Tree, Error>::okClass(newTree);
}

string Tree::toString() const {
    if (root == NULL) return "";
    return root->toString();
}

void Tree::print() const {
    cout << toString() << endl;
}

void Tree::getVars(string*& vars, int& count) const {
    count = 0;
    int capacity = 0;

    if (root != NULL) {
        root->getVariables(vars, count, capacity);
    }
}

void Tree::printVars() const {
    string* vars = NULL;
    int count = 0;
    getVars(vars, count);

    for (int i = 0; i < count; i++) {
        cout << vars[i];
        if (i < count - 1) cout << " ";
    }
    cout << endl;

    delete[] vars;
}

bool Tree::compute(const double* values, int valueCount) const {
    if (root == NULL) {
        cout << "Blad: brak drzewa" << endl;
        return false;
    }

    string* vars = NULL;
    int varCount = 0;
    getVars(vars, varCount);

    if (valueCount != varCount) {
        cout << "Blad: liczba wartosci (" << valueCount << ") nie odpowiada liczbie zmiennych (" << varCount << ")" << endl;
        delete[] vars;
        return false;
    }

    double result = root->evaluate(values, vars, varCount);
    cout << "Wynik: " << result << endl;

    delete[] vars;
    return true;
}

int Tree::altitude(Node* root) const {
    if (root == NULL) return -1;

    int childrenCount = root->getChildrenCount();

    if (childrenCount == 0) {
        return 0;
    }

    else if (childrenCount == 1) {
        return 1 + altitude(root->getChild(0));
    }

    else if (childrenCount == 2) {
        return 1 + max( altitude(root->getChild(0)),
                        altitude(root->getChild(1)) );
    }

    return 0;
}

string Tree::draw() const
{
    if (root == 0) return "Brak drzewa\n";

    int H = altitude(root);
    int maxWidth = 1 << H;  // 2^H

    struct NodePos {
        Node* node;
        int level;
        int position;
    };

    NodePos* positions = new NodePos[1000];
    int posCount = 0;

    struct QueueItem {
        Node* node;
        int level;
        int left;
        int right;
    };

    QueueItem* queue = new QueueItem[1000];
    int front = 0, back = 0;

    queue[back].node = root;
    queue[back].level = 0;
    queue[back].left = 0;
    queue[back].right = maxWidth - 1;
    back++;

    while (front < back) {
        QueueItem current = queue[front++];

        int mid = (current.left + current.right) / 2;

        // Zapisz pozycję węzła
        positions[posCount].node = current.node;
        positions[posCount].level = current.level;
        positions[posCount].position = mid;
        posCount++;

        // Dodaj dzieci
        int childCount = current.node->getChildrenCount();
        if (childCount > 0) {
            int rangePerChild = (current.right - current.left + 1) / childCount;

            for (int i = 0; i < childCount; i++) {
                Node* child = current.node->getChild(i);
                if (child != 0) {
                    queue[back].node = child;
                    queue[back].level = current.level + 1;
                    queue[back].left = current.left + i * rangePerChild;
                    queue[back].right = current.left + (i + 1) * rangePerChild - 1;
                    back++;
                }
            }
        }
    }

    delete[] queue;

    string result = "";

    for (int lvl = 0; lvl <= H; lvl++) {
        string line = "";
        for (int i = 0; i < maxWidth; i++) {
            line += ' ';
        }

        // Gwiazdki
        for (int i = 0; i < posCount; i++) {
            if (positions[i].level == lvl) {
                line[positions[i].position] = '*';
            }
        }

        result += line + "\n";
    }

    delete[] positions;

    return result;
}



void Tree::setRoot(Node* node) {
    root = node;
    setCounterForTree(root);
}

void Tree::setCounter(OperationCounter* cnt) {
    counterTree = cnt;
    setCounterForTree(root);
}