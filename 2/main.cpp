#include <iostream>

#include "CNumber.h"

using namespace std;

int main() {

    int *tab;
    tab = new int[50];

    CNumber firstTest, secondTest, thirdTest, fourthTest, fifthTest, sixthTest;
    CNumber firstResult, secondResult, thirdResult, fourthResult, fifthResult;
    firstTest = 30;
    secondTest = 151;
    thirdTest = -15;
    fourthTest = 10000;
    fifthTest = INT_MAX;
    sixthTest = INT_MIN;


    firstResult = secondTest+firstTest;
    firstResult.printObj();

    cout << "/n";

    secondResult = fifthTest*secondTest;
    secondResult.printObj();



    //c_num_2.printObj();


    return 0;
}