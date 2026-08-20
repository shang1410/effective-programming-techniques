//
// Created by XYZ on 13.12.2025.
//

#include "OperationCounter.h"

#include <iostream>

using namespace std;


OperationCounter::OperationCounter() {
    reset();
}

void OperationCounter::reset() {
    copyConstructorCount = 0;
    moveConstructorCount = 0;
    copyAssignmentCount = 0;
    moveAssignmentCount = 0;
    cloneCount = 0;
}

void OperationCounter::incrementCopyConstructor() {
    copyConstructorCount++;
}

void OperationCounter::incrementMoveConstructor() {
    moveConstructorCount++;
}

void OperationCounter::incrementCopyAssignment() {
    copyAssignmentCount++;
}

void OperationCounter::incrementMoveAssignment() {
    moveAssignmentCount++;
}

void OperationCounter::incrementClone() {
    cloneCount++;
}

int OperationCounter::getCopyConstructorCount() const {
    return copyConstructorCount;
}

int OperationCounter::getMoveConstructorCount() const {
    return moveConstructorCount;
}

int OperationCounter::getCopyAssignmentCount() const {
    return copyAssignmentCount;
}

int OperationCounter::getMoveAssignmentCount() const {
    return moveAssignmentCount;
}

int OperationCounter::getCloneCount() const {
    return cloneCount;
}

int OperationCounter::getTotalCopies() const {
    return copyConstructorCount + copyAssignmentCount + cloneCount;
}

int OperationCounter::getTotalMoves() const {
    return moveConstructorCount + moveAssignmentCount;
}

void OperationCounter::print(const string& label) const {
    cout << "\n" << endl;
    cout << "Konstruktor kopiujacy:         " << copyConstructorCount << endl;
    cout << "Konstruktor przenoszacy:       " << moveConstructorCount << endl;
    cout << "Operator= kopiujacy:           " << copyAssignmentCount << endl;
    cout << "Operator= przenoszacy:         " << moveAssignmentCount << endl;
    cout << "Operacji clone() (deep copy):  " << cloneCount << endl;
    cout << "\n" << endl;
    cout << "RAZEM kopiowan:                " << getTotalCopies() << endl;
    cout << "RAZEM przeniesien:             " << getTotalMoves() << endl;
    cout << "\n" << endl;
}