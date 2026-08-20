#include <iostream>
#include "CNumber.h"
#include "ComplexNumber.h"


// using namespace std;
//
// int main() {
//
//     int *tab;
//     tab = new int[50];
//
//     CNumber firstTest, secondTest, thirdTest, fourthTest, fifthTest, sixthTest;
//     CNumber firstResult, secondResult, thirdResult, fourthResult, fifthResult;
//     firstTest = 3;
//     secondTest = 2;
//     thirdTest = -15;
//     fourthTest = 10000;
//     fifthTest = INT_MAX;
//     sixthTest = INT_MIN;
//
//
//     firstResult = firstTest*secondTest;
//     firstResult.printObj();
//
//     cout << "/n";
//
//     secondResult = fifthTest-secondTest;
//     secondResult.printObj();
//
//
//
//     //c_num_2.printObj();
//
//
//     return 0;
// }



int main() {
    ComplexNumber a(5, 2);
    ComplexNumber b(3, -7);
    CNumber abc;
    abc = 5;

    ComplexNumber c = abc+a;

    c.printString();
}