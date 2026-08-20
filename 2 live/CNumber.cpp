//
// Created by XYZ on 1.11.2025.
//

#include "CNumber.h"
#include "Constans.h"
#include <iostream>

using namespace std;

CNumber::CNumber() {
    iLength = defaultLenght;
    piNumber = new int[iLength];

    for (int i = 0; i < iLength; i++)
        piNumber[i] = 0;

    isNegative = false;
}

CNumber::CNumber(const CNumber &other) {
    iLength = other.iLength;
    isNegative = other.isNegative;
    piNumber = new int[iLength];
    for (int i = 0; i < iLength; i++)
        piNumber[i] = other.piNumber[i];
}

CNumber::~CNumber() {
    delete[] piNumber;
}

void CNumber::operator=(const int iValue) {
    int tempLength = 0;
    int tempValue = iValue;

    // Znak
    if (iValue < 0) {
        this->isNegative = true;
        tempValue = -tempValue;
    } else {
        this->isNegative = false;
    }

    if (tempValue == 0) {
        tempLength = 1;
    } else {
        int temp = tempValue;
        while (temp > 0) {
            temp = temp / 10;
            tempLength++;
        }
    }

    // Czyszczenie starej pamięci na zapas
    delete[] piNumber;

    this->iLength = tempLength;
    this->piNumber = new int[tempLength];

    // od indeksu 0 (najmniej znacząca)
    for (int i = 0; i < tempLength; i++) {
        this->piNumber[i] = tempValue % 10;
        tempValue = tempValue / 10;
    }
}

// void CNumber::operator=(const CNumber &pcOther)
// {
//     piNumber = pcOther.piNumber;
//     iLength = pcOther.iLength;
// }

void CNumber::operator=(const CNumber &pcOther){
    if (this == &pcOther) {
        return;
    }

    delete[] piNumber;

    iLength = pcOther.iLength;
    isNegative = pcOther.isNegative;
    piNumber = new int[iLength];

    for (int i = 0; i < iLength; i++) {
        piNumber[i] = pcOther.piNumber[i];
    }
}

CNumber CNumber::operator+(const CNumber &pcNewVal) {
    // znak taki sam
    if (this->isNegative == pcNewVal.isNegative) {
        CNumber sum = this->addition(pcNewVal);
        sum.isNegative = this->isNegative;
        return sum;
    }

    // A+(-B)
    else if (!this->isNegative && pcNewVal.isNegative) {
        CNumber temp = pcNewVal;
        temp.isNegative = false;
        return (*this) - temp;
    }

    // (-A) + B = B - A
    else {
        CNumber temp = *this;
        temp.isNegative = false;

        // pcNewVal jest const, czyli kopia
        CNumber left = pcNewVal;
        return left - temp;
    }

}

CNumber CNumber::operator-(const CNumber &pcNewVal) {
    // A - (-B) = A + B
    if (!this->isNegative && pcNewVal.isNegative) {
        CNumber temp = pcNewVal;
        temp.isNegative = false;
        return (*this) + temp;
    }

    // (-A) - B = -(A + B)
    if (this->isNegative && !pcNewVal.isNegative) {
        CNumber left = *this;
        left.isNegative = false;

        CNumber tmp = left + pcNewVal;
        tmp.isNegative = true;
        return tmp;
    }

    // (-A) - (-B) = B - A
    if (this->isNegative && pcNewVal.isNegative) {
        CNumber A = *this;
        CNumber B = pcNewVal;
        A.isNegative = false;
        B.isNegative = false;

        return B - A;
    }

    CNumber result;
    delete[] result.piNumber;


    // która liczba jest większa bezwzględnie
    int cmp = compare(*this, pcNewVal);

    // wybieramy większą jako "big", mniejszą jako "small"
    const CNumber *big;
    const CNumber *small;
    bool negativeResult = false;

    if (cmp >= 0) {
        big = this;
        small = &pcNewVal;
    } else {
        big = &pcNewVal;
        small = this;
        negativeResult = true;
    }

    result.iLength = big->iLength;
    result.piNumber = new int[result.iLength];

    int borrow = 0;

    for (int i = 0; i < result.iLength; i++) {
        int a = (i < big->iLength ? big->piNumber[i] : 0);
        int b = (i < small->iLength ? small->piNumber[i] : 0);

        int diff = a - b - borrow;

        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        result.piNumber[i] = diff;
    }

    int newLength = result.iLength;

    while (newLength > 1 && result.piNumber[newLength - 1] == 0)
        newLength--;

    if (newLength != result.iLength) {
        int *newTable = new int[newLength];
        for (int i = 0; i < newLength; i++)
            newTable[i] = result.piNumber[i];

        delete[] result.piNumber;
        result.piNumber = newTable;
        result.iLength = newLength;
    }

    result.isNegative = negativeResult;

    if (result.iLength == 1 && result.piNumber[0] == 0)
        result.isNegative = false;

    return result;
}

CNumber CNumber::operator*(const CNumber &pcNewVal) const
{
    bool negativeResult = (this->isNegative != pcNewVal.isNegative);

    CNumber A = *this;
    CNumber B = pcNewVal;
    A.isNegative = false;
    B.isNegative = false;

    // zwroc 0 jezeli jedna z nich to zero
    if (isZero(A) || isZero(B)) {
        CNumber zero;
        zero = 0;
        zero.isNegative = false;
        return zero;
    }

    int resLen = A.iLength + B.iLength;
    int *res = new int[resLen];

    for (int i = 0; i < resLen; i++)
        res[i] = 0;

    //mnozenie
    for (int i = 0; i < A.iLength; i++) {
        int carry = 0;

        for (int j = 0; j < B.iLength; j++) {
            int mul = A.piNumber[i] * B.piNumber[j] + res[i + j] + carry;

            res[i + j] = mul % 10;
            carry = mul / 10;
        }

        if (carry > 0) {
            res[i + B.iLength] += carry;
        }
    }

    //ustalanie nowego len
    int finalLength = resLen;
    while (finalLength > 1 && res[finalLength - 1] == 0)
        finalLength--;


    CNumber result;
    delete[] result.piNumber;

    result.iLength = finalLength;
    result.piNumber = new int[finalLength];
    for (int i = 0; i < finalLength; i++)
        result.piNumber[i] = res[i];

    delete[] res;

    //znak
    result.isNegative = negativeResult;

    // znak dla 0
    if (result.iLength == 1 && result.piNumber[0] == 0)
        result.isNegative = false;

    return result;
}

CNumber CNumber::operator/(const CNumber &pcNewVal) {
    CNumber result;
    delete[] result.piNumber;

    // dzielenie przez 0
    if (pcNewVal.iLength == 1 && pcNewVal.piNumber[0] == 0) {
        result.iLength = 1;
        result.piNumber = new int[1];
        result.piNumber[0] = 0;
        result.isNegative = false;
        return result;
    }

    // długość wyniku
    result.iLength = this->iLength;
    result.piNumber = new int[result.iLength];
    for (int i = 0; i < result.iLength; i++)
        result.piNumber[i] = 0;


    CNumber dividend = *this;
    dividend.isNegative = false;

    CNumber divisor = pcNewVal;
    divisor.isNegative = false;

    // początkowa reszta = 0
    CNumber remainder;
    remainder = 0;

    CNumber ten;
    ten=TEN;

    // dzielenie pisemne
    for (int i = iLength - 1; i >= 0; i--) {

        // przesunięcie reszty w lewo
        remainder = remainder * ten;

        // dodanie aktualnej cyfry z dzielnej
        CNumber digit;
        digit = dividend.piNumber[i];

        remainder = remainder + digit;

        // szukamy ile razy dzielnik mieści się w remainder
        int q = 0;
        while (compare(remainder, divisor) >= 0) {
            remainder = remainder - divisor;
            q++;
        }

        result.piNumber[i] = q;
    }

    // usuwanie wiodących zer
    int nl = result.iLength;
    while (nl > 1 && result.piNumber[nl - 1] == 0)
        nl--;

    if (nl != result.iLength) {
        int *nt = new int[nl];
        for (int i = 0; i < nl; i++)
            nt[i] = result.piNumber[i];
        delete[] result.piNumber;
        result.piNumber = nt;
        result.iLength = nl;
    }

    result.isNegative = (this->isNegative != pcNewVal.isNegative);

    if (result.iLength == 1 && result.piNumber[0] == 0)
        result.isNegative = false;

    return result;
}

CNumber CNumber::addition(const CNumber &other) {
    CNumber result;
    delete[] result.piNumber;

    // maksymalna długość = max(len(A), len(B)) + 1
    result.iLength = ((iLength > other.iLength) ? iLength : other.iLength) + 1;
    result.piNumber = new int[result.iLength];

    result.isNegative = false;
    int a, b, sum;
    int carry = 0;

    for (int i = 0; i < result.iLength; i++) {

        a = (i < this->iLength ? this->piNumber[i] : 0);
        b = (i < other.iLength ? other.piNumber[i] : 0);

        sum = a + b + carry;
        result.piNumber[i] = sum % 10;
        carry = sum / 10;
    }

    // skrócenie tablicy
    int newLength = result.iLength;

    while (newLength > 1 && result.piNumber[newLength - 1] == 0)
        newLength--;

    if (newLength != result.iLength) {
        int *newTable = new int[newLength];
        for (int i = 0; i < newLength; i++)
            newTable[i] = result.piNumber[i];

        delete[] result.piNumber;
        result.piNumber = newTable;
        result.iLength = newLength;
    }

    return result;
}

void CNumber::printObj() {
    cout << "Liczba cyfr: " << this->iLength << " " << "negFlag = " << (this->isNegative ? "true":"false") << "\nWartosc: " ;

    if (this->isNegative) {
        cout << "-";
    }

    for (int i = this->iLength - 1; i >= 0; i--) {
        cout << *(this->piNumber+i);
    }
    cout << endl;
}


int CNumber::compare(const CNumber &A, const CNumber &B){
    if (A.iLength > B.iLength) return 1;
    if (A.iLength < B.iLength) return -1;

    for (int i = A.iLength - 1; i >= 0; --i) {
        if (A.piNumber[i] > B.piNumber[i]) return 1;
        if (A.piNumber[i] < B.piNumber[i]) return -1;
    }

    return 0;
}

bool CNumber::isZero(const CNumber &A) const{
    if (A.iLength == 0) return true;
    for (int i = 0; i < A.iLength; i++)
        if (A.piNumber[i] != 0)
            return false;

    return true;
}


