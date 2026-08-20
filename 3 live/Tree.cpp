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

Tree::Tree(const Tree& other) {
    root = NULL;
    if (other.root != NULL) {
        root = other.root->clone();
    }
}

Tree::~Tree() {
    delete root;
}

Tree& Tree::operator=(const Tree& other) {
    if (this != &other) {
        delete root;
        if (other.root != NULL) {
            root = other.root->clone();
        } else {
            root = NULL;
        }
    }
    return *this;
}

Tree Tree::operator+(const Tree& other) const {
    Tree result(*this);

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
        return result;
    }

    result.findFirstLeaf(result.root, leafParent, leafIndex);

    if (leafParent != NULL && leafIndex >= 0) {
        leafParent->setChild(leafIndex, other.root->clone());
    }

    return result;
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

Node* Tree::buildTree(const TokenList& tokens, int& index, bool& modified) {
    if (index >= tokens.getCount()) {
        modified = true;
        return new ConstantNode(1);
    }

    string token = tokens.get(index);
    index++;

    if (isOperator(token)) {
        OperatorNode* node = new OperatorNode(token);
        int required = node->getRequiredArgs();

        for (int i = 0; i < required; i++) {
            Node* child = buildTree(tokens, index, modified);
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
        modified = true;
        return new ConstantNode(1);
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

bool Tree::enter(const string& formula) {
    TokenList tokens;
    istringstream iss(formula);
    string token;

    while (iss >> token) {
        tokens.add(token);
    }

    if (tokens.getCount() == 0) {
        delete root;
        root = new ConstantNode(1);
        cout << "Blad: puste wyrazenie. Poprawiono na: 1" << endl;
        return false;
    }

    int index = 0;
    bool modified = false;
    Node* newRoot = buildTree(tokens, index, modified);

    if (index < tokens.getCount()) {
        cout << "Ostrzezenie: zignorowano nadmiarowe symbole" << endl;
        modified = true;
    }

    delete root;
    root = newRoot;

    if (modified) {
        cout << "Wyrazenie zostalo poprawione na: " << toString() << endl;
    }

    return true;
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
    if (root == NULL) return "Brak drzewa\n";

    int H = altitude(root);
    int maxLevels = H + 1;


    Node*** levels = new Node**[maxLevels];    //tablica 2D, której celem jest przechowywanie na każdej z poziomow nodow
    int* levelCounts = new int[maxLevels];     //liczba nodow na kazdym poziomie

    for (int i = 0; i < maxLevels; i++) {
        levels[i] = NULL;
        levelCounts[i] = 0;
    }



    Node** queue = new Node*[1000];         // kolejka
    int* queueLevel = new int[1000];        //poziom kazdego node'a

    int front = 0, back = 0;
    //wyznaczniki a) ktory node obslugujemy aktualnie b) gdzie znajduje sie ostatni node

    // wrzucenie korzenia
    queue[back] = root;
    queueLevel[back] = 0;
    back++;

    while (front < back) {
        Node* tempNode = queue[front];   //aktualny node
        int lvl = queueLevel[front];     //poziom aktualnego nodea

        // dodanie node do levels[lvl]
        int oldCount = levelCounts[lvl];
        Node** newArr = new Node*[oldCount + 1];


        // START, realokacja, bo levels nie ma określonej długości w 2 wymiarach
        for (int i = 0; i < oldCount; i++) {
            newArr[i] = levels[lvl][i];
        };

        newArr[oldCount] = tempNode;

        delete[] levels[lvl];
        levels[lvl] = newArr;
        levelCounts[lvl]++;
        // END, realokacja

        // dzieci do kolejki
        int count = tempNode->getChildrenCount();
        for (int i = 0; i < count; i++) {
            queue[back] = tempNode->getChild(i);
            queueLevel[back] = lvl + 1;
            back++;
        }

        front++;
    }

    delete[] queue;
    delete[] queueLevel;


    string result = "";

    for (int lvl = 0; lvl < maxLevels; lvl++) {

        int spacing = 1 << (H - lvl);     // 2^(H-lvl)
        string line = "";

        // pierwszy odstęp
        for (int i = 0; i < spacing; i++)
            line += ' ';

        // gwiazdki
        for (int i = 0; i < levelCounts[lvl]; i++) {
            line += "*";

            // odstęp między gwiazdkami
            if (i < levelCounts[lvl] - 1) {
                for (int j = 0; j < spacing * 2; j++)
                    line += ' ';
            }
        }

        result += line + "\n";
    }

    for (int i = 0; i < maxLevels; i++) {
        delete[] levels[i];
    }
    delete[] levels;
    delete[] levelCounts;

    return result;
}