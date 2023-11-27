#include <iostream>
#include <vector>
#include "time.h"

using namespace std;

template<typename T>

using arrayT = vector<T>;

int main() {
    srand(time(0));

    int power = 2;                             // (1)
    arrayT<double> koefs(power + 1);           // (2)

    for (int i = 0; i <= power; ++i) {         // (3)
        koefs[i] = rand() % 10 - 5;            // (4)
        cout << "Коэффициент при x^"           
             << power - i << ": " 
             << koefs[i] << endl;
    }

    int n = 5;                                 // (5)          
    arrayT<double> xValues(n);                 // (6)
    
    for (int i = 0; i < n; ++i)                // (7)
        xValues[i] = rand() % 10 - 5;          // (8)

    for (int i = 0; i < n; ++i) {              // (9)

        double x = xValues[i],                 // (10)
               cur,                            // (11)
               prev;                           // (12)
        
        for (int j = 0; j <= power; ++j) {     // (13)

            cur = koefs[j];                    // (14)

            if (j)                             // (15)
                prev = cur + x * prev;         // (16)
            else
                prev = cur;                    // (17)
        }

        cout << "Результа для x = "            // (18)
             << xValues[i] << ": " 
             << prev << endl;
    }
}