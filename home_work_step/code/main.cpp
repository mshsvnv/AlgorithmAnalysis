#include <iostream>
#include <vector>
#include "time.h"

using namespace std;

template<typename T>

using arrayT = vector<T>;

int main() {
    srand(time(0));

    int power = 5;                                      // (1)
    arrayT<double> koefs(power + 1);                    // (2)

    for (int i = 0; i <= power; ++i) {                  // (3)
        koefs[i] = rand() % 100 - 50;                   // (4)
        cout << "Коэффициент при x^"                   // (5)
             << power - i << ": " 
             << koefs[i] << endl;
    }

    arrayT<double> tmp(power + 1);                      // (6)
    double x = 1;                                       // (7)

    for (int i = 0; i <= power; ++i) {                  // (8)

        tmp[i] = koefs[i];                              // (9)

        if (i)                                          // (10)
            tmp[i] += x * tmp[i - 1];                   // (11)
    }

    cout << "\nРезультат: " << tmp[power];              // (12)
}