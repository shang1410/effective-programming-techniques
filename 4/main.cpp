// #include "Interface.h"
//
//
// int main() {
//
//     Interface interface;
//     interface.run();
//     return 0;
// }

#include <iostream>
#include <thread>

int main() {
    unsigned int n = std::thread::hardware_concurrency();
    if (n == 0) {
        std::cout << "Nie można wykryć liczby wątków.\n";
    } else {
        std::cout << "Liczba wątków dostępnych: " << n << "\n";
    }
}