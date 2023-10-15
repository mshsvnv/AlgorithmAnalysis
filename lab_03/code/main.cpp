#include "inc/sorts.h"
#include "inc/measure.h"

#define MAX_AMOUNT 1000
#define ITERS 100

int menu() {

    int choice;

    cout << "\n\t\tМеню\n"
    "1. Radix sort\n"
    "2. Comb sort;\n"
    "3. Shell sort\n"
    "4. Замерить время\n"
    "0. Выход\n\n"
    "Выберете пункт (0-4): ";

    cin >> choice;
    wcout << endl;

    return choice;
}

int main() {

    // int choice = menu();

    arrayT arr{1, 1, 1, 1};
    
    vector<Sort*> sorts{new Radix, new Comb, new Shell};

    sorts[0]->execute(arr);
    
    // while (choice) {
    //     choice = menu();
    // }

    for (auto elem : arr)
        cout << elem << " ";
    cout << endl;
}
