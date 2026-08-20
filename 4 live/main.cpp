#include <iostream>
#include "Union.hpp"

using namespace std;

int main() {
    Union<int, double> u(5);
    cout << u.isFirst() << endl;
    cout << u.isSecond() << endl;
    cout << u.getFirst() << endl;
    u = 4.0;

    cout << u.isFirst() << endl;
    cout << u.isSecond() << endl;
    cout << u.getSecond() << endl;

    //Union<int, double> u4;
}