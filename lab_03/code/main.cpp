#include "inc/sorts.h"
#include "inc/measure.h"
#include "inc/array.h"

#define MAX_AMOUNT 100
#define ITERS 100

int menu() {

    int choice;

    cout << "\n\t\tМеню\n"
    "1. Radix sort\n"
    "2. Comb sort;\n"
    "3. Shell sort\n\n"
    "4. Замерить время\n"
    "5. Замерить память\n"
    "0. Выход\n\n"
    "Выберете пункт (0-4): ";

    cin >> choice;
    cout << endl;

    return choice;
}

int main() {

    int choice = menu();

    vector<Sort*> sorts{new Radix, new Comb, new Shell};
    
    while (choice) {

        if (choice == 4) {
            timeMeasure(10, ITERS, MAX_AMOUNT, 0);
            timeMeasure(10, ITERS, MAX_AMOUNT, 1);
            timeMeasure(10, ITERS, MAX_AMOUNT, 2);
            timeMeasure(10, ITERS, MAX_AMOUNT, 3);
        }
        else if (choice == 5) {

            }
        else{

            ArrayT arr("../code/data.txt");

            if (!arr.size())
                cout << "Некорректные данные!\n";
            else {
                cout << "До: " << arr;
                sorts[choice - 1]->execute(arr);
                cout << "После: " << arr; 
            }
        }

        choice = menu();
    }
}
