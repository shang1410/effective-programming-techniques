//
// Created by XYZ on 13.12.2025.
//

#ifndef LISTA5_OPERATIONCOUNTER_H
#define LISTA5_OPERATIONCOUNTER_H
#include <string>
#include <iostream>

using namespace std;

class OperationCounter {
private:
    int copyConstructorCount;
    int moveConstructorCount;
    int copyAssignmentCount;
    int moveAssignmentCount;
    int cloneCount;

public:
    OperationCounter();

    void reset();

    void incrementCopyConstructor();
    void incrementMoveConstructor();
    void incrementCopyAssignment();
    void incrementMoveAssignment();
    void incrementClone();

    int getCopyConstructorCount() const;
    int getMoveConstructorCount() const;
    int getCopyAssignmentCount() const;
    int getMoveAssignmentCount() const;
    int getCloneCount() const;

    int getTotalCopies() const;

    int getTotalMoves() const;

    void print(const string& label) const;
};


#endif //LISTA5_OPERATIONCOUNTER_H