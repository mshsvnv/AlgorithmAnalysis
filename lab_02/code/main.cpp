#include "inc/matrix.h"
#include "inc/multiply.h"
#include "inc/measure.h"

#define MAX_AMOUNT 1000
#define ITERS 100

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

    MatrixT mtr1("../data.txt");
    MatrixT mtr2("../data.txt");

    vector<Multiply*> muls{new Standard, new Vinograd, new VinogradOpt};

    while (choice) {

        if (choice == 4)
            timeMeasure(ITERS, MAX_AMOUNT);
        else {

            MatrixT res = (muls[choice - 1])->multiply(mtr1, mtr2);

            cout << "Первая матрица:\n" << mtr1 << endl;
            cout << "Вторая матрица:\n" << mtr2 << endl;
            cout << "Результирующая матрица:\n" << res << endl;
        }

        choice = menu();
    }
}
