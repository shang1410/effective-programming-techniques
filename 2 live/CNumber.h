//
// Created by XYZ on 1.11.2025.
//

#ifndef LISTA_2_CNUMBER_H
#define LISTA_2_CNUMBER_H




class CNumber {

    public:
        CNumber();
        ~CNumber();


        CNumber(const CNumber &other);

        void operator=(int iNewValue);
        void operator=(const CNumber &pcOther);

        CNumber operator+(const CNumber &pcNewVal);
        CNumber operator-(const CNumber &pcNewVal);
        CNumber operator*(const CNumber &pcNewVal) const;
        CNumber operator/(const CNumber &pcNewVal);
        int compare(const CNumber &A, const CNumber &B);
        bool isZero(const CNumber &A) const;
        void printObj();



        void setIsNegative(bool b) {
            isNegative = b;
        }

        int getIsNegative() {
            return isNegative;
        }


    private:
        int *piNumber;
        int iLength;
        bool isNegative;

        CNumber addition(const CNumber &other);
};


#endif //LISTA_2_CNUMBER_H