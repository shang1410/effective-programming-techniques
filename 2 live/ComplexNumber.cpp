//
// Created by XYZ on 5.11.2025.
//

#include "ComplexNumber.h"

#include <iostream>
#include <ostream>

using namespace std;


ComplexNumber::ComplexNumber() {
    realNumber = 0;
    imaginaryNumber = 0;
}

ComplexNumber::ComplexNumber(int realNumber, int imaginaryNumber) {
    this->realNumber = realNumber;
    this->imaginaryNumber = imaginaryNumber;
}


ComplexNumber ComplexNumber::operator+(const ComplexNumber &pcNewVal) {
    ComplexNumber result;

    result.realNumber = realNumber + pcNewVal.realNumber;
    result.imaginaryNumber = imaginaryNumber + pcNewVal.imaginaryNumber;

    return result;
}

ComplexNumber ComplexNumber::operator-(const ComplexNumber &pcNewVal) {
    ComplexNumber result;

    result.realNumber = realNumber - pcNewVal.realNumber;
    result.imaginaryNumber = imaginaryNumber - pcNewVal.imaginaryNumber;

    return result;
}

ComplexNumber ComplexNumber::operator*(const ComplexNumber &pcNewVal) {
    ComplexNumber result;

    result.realNumber = (realNumber * pcNewVal.realNumber - imaginaryNumber * pcNewVal.imaginaryNumber);
    result.imaginaryNumber = (realNumber * pcNewVal.imaginaryNumber + pcNewVal.realNumber * imaginaryNumber);

    return result;
}

ComplexNumber ComplexNumber::operator/(const ComplexNumber &pcNewVal) {
    ComplexNumber result;

    result.realNumber =
        ((realNumber * pcNewVal.realNumber) +
         (imaginaryNumber * pcNewVal.imaginaryNumber)) /
        ((pcNewVal.realNumber * pcNewVal.realNumber) +
         (pcNewVal.imaginaryNumber * pcNewVal.imaginaryNumber));

    result.imaginaryNumber =
        ((imaginaryNumber * pcNewVal.realNumber) -
         (realNumber * pcNewVal.imaginaryNumber)) /
        ((pcNewVal.realNumber * pcNewVal.realNumber) +
         (pcNewVal.imaginaryNumber * pcNewVal.imaginaryNumber));

    return result;
}


ComplexNumber operator+(const CNumber &lhs, const ComplexNumber &rhs) {
    ComplexNumber result;

    result.realNumber = lhs + rhs.realNumber;
    result.imaginaryNumber = rhs.imaginaryNumber;

    return result;
}



//
// ComplexNumber ComplexNumber::operator-(const CNumber &pcNewVal) {
//
// }
// ComplexNumber ComplexNumber::operator*(const CNumber &pcNewVal) {
//
// }
// ComplexNumber ComplexNumber::operator/(const CNumber &pcNewVal) {
//
// }

ComplexNumber ComplexNumber::operator~() {
    ComplexNumber result;

    result.realNumber = this->realNumber;
    result.imaginaryNumber = this->imaginaryNumber;

    if (this->imaginaryNumber.getIsNegative() == true) {
        result.imaginaryNumber.setIsNegative(false);
    }
    else {
        result.imaginaryNumber.setIsNegative(true);
    }

    return result;
}






void ComplexNumber::printString() {
    cout << "Rzeczywista liczba: ";
    cout << endl;
    realNumber.printObj();
    cout << endl;
    cout << "Urojona liczba: ";
    cout << endl;
    imaginaryNumber.printObj();
    cout << endl;
    cout << endl;
}
