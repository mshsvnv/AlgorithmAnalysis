#include "inc/matrix.h"

int menu() {

    int choice;

    cout << "\n\t\tМеню\n"
    "1. Стандартный метод\n"
    "2. Алгоритм Винограда;\n"
    "3. Оптимизированный п. 2\n"
    "4. Замерить время\n"
    "0. Выход\n\n"
    "Выберете пункт (0-4): ";

    cin >> choice;
    wcout << endl;

    return choice;
}

int main() {

    int choice = menu();
    int rc = 0;

    bool square = false;

    MatrixT mtr1("../code/data.txt");


    // while (choice) {

        
    //     choice = menu();
    // }
}