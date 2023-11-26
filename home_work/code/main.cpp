#include <iostream>
#include <vector>
#include "time.h"

using namespace std;

using arrayT = vector<int>;

int main() {

srand(time(0));

int size = 4;                                                //(1)
arrayT arr(size);                                            //(2)

for (int i = 0; i < size; ++i)                                      
    arr[i] = rand() % 100 - 50;                                     

cout << "До: ";
for (auto elem : arr)                                               
    cout << elem << " ";                                            
cout << endl;

for (int step = 1; step < size; step = step * 2){            //(3)

    for (int left = 0; left < size - 1; left += 2 * step){   //(4)

        int mid = min(left + step - 1, size - 1),            //(5)
            right = min(left + 2 * step - 1, size - 1);      //(6)

        int i = left,                                        //(7)
            j = mid + 1,                                     //(8)
            pos = 0,                                         //(9)
            len = right - left + 1;                          //(10)

        arrayT tmp(len);                                     //(11)

        while (i <= mid || j <= right) {                     //(12)

            if (i <= mid && (j > right || arr[i] < arr[j])) {//(13)
                tmp[pos] = arr[i];                           //(14)
                i++;                                         //(15)
            } 
            else {
                tmp[pos] = arr[j];                           //(16) 
                j++;                                         //(17) 
            }
            pos++;                                           //(18) 
        }

        for (int k = 0; k < len; ++k)                        //(19)
            arr[k + left] = tmp[k];                          //(20)
    }
}

    cout << "После: ";                                                  
    for (auto elem : arr)                                               
        cout << elem << " ";                                            
    cout << endl;
}