#include "inc/matrix.h"
#include "inc/multiply.h"
#include "inc/measure.h"

#define MAX_AMOUNT 1000
#define ITERS 100

int menu() {

    int choice;

    cout << "\n\t\tМеню\n"
    "1. Стандартный метод;\n"
    "2. Алгоритм Винограда;\n"
    "3. Оптимизированный п. 2;\n"
    "4. Замерить время;\n"
    "0. Выход.\n\n"
    "Выберете пункт (0-4): ";

    cin >> choice;
    wcout << endl;

    return choice;
}

int main() {

    int choice = menu();

    vector<Multiply*> muls{new Standard, new Vinograd, new VinogradOpt};

    while (choice) {

        bool mul = false;

        if (choice == 4)
            timeMeasure(ITERS, MAX_AMOUNT);
        else {
            MatrixT mtr1("../data/mtr1.txt");
            MatrixT mtr2("../data/mtr2.txt");

            if (mtr1.m_columns * mtr1.m_rows * mtr2.m_columns * mtr2.m_rows == 0) {
                cout << "Некорректный размер матрицы!" << endl;
            }
            else if (choice == 1) {

                if (mtr1.m_columns != mtr2.m_rows) 
                    cout << "Количество столбцов первой матрицы не совпадает с количеством строк второй!";
            }
            else if (choice == 2 || choice == 3) {
             
                if (!(mtr1.m_rows == mtr1.m_columns && mtr2.m_rows == mtr2.m_columns && mtr1.m_rows == mtr2.m_columns)) 
                    cout << "Методом Винограда можно умножать только квадратные матрицы!";
            }
            else
                mul = true;

            if (mul) {
                MatrixT res = (muls[choice - 1])->multiply(mtr1, mtr2);

                cout << "Первая матрица:\n" << mtr1 << endl;
                cout << "Вторая матрица:\n" << mtr2 << endl;
                cout << "Результирующая матрица:\n" << res << endl;
            }
        }

        choice = menu();
    }

    cout << "Завершение работы!";
}
