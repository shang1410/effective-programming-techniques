//
// Created by XYZ on 5.11.2025.
//

#ifndef LIVE_2_05_11_COMPLEXNUMBER_H
#define LIVE_2_05_11_COMPLEXNUMBER_H

#include "ComplexNumber.h"
#include "CNumber.h"



class ComplexNumber {
public:
    ComplexNumber();
    ComplexNumber(int realNumber, int imaginaryNumber);

    ComplexNumber operator+(const ComplexNumber &pcNewVal);
    ComplexNumber operator-(const ComplexNumber &pcNewVal);
    ComplexNumber operator*(const ComplexNumber &pcNewVal);
    ComplexNumber operator/(const ComplexNumber &pcNewVal);

    ComplexNumber operator+(const CNumber &pcNewVal) const;
    ComplexNumber operator-(const CNumber &pcNewVal);
    ComplexNumber operator*(const CNumber &pcNewVal);
    ComplexNumber operator/(const CNumber &pcNewVal);


    void setReal(int real) {
        realNumber = real;
    }

    CNumber getReal() {
        return realNumber;
    }

    void setImaginary(int imaginary) {
        imaginaryNumber = imaginary;
    }

    CNumber getImaginary() {
        return imaginaryNumber;
    }



    ComplexNumber operator~();

    void printString();

private:
    CNumber realNumber;
    CNumber imaginaryNumber;


};


ComplexNumber operator+(const CNumber &lhs, const ComplexNumber &rhs);



#endif //LIVE_2_05_11_COMPLEXNUMBER_H