#include <iostream>

#include "inc/input.h"

using namespace std;

int menu() {

    int choice;

    cout << L"\n\t\tМеню\n"
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

    int** mtr = nullptr;

    bool square = false;

    while (choice) {

        if (choice) {

            if (choice != 1)
                square = true;

            // rc = readMtr(square);
            

        }
        else
            wcout << L"Завершение!\n";

        choice = menu();
    }
}