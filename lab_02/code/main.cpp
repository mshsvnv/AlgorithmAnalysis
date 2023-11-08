#include "inc/matrix.h"
#include "inc/multiply.h"
#include "inc/measure.h"

#define MAX_AMOUNT_ORD 100
#define MAX_AMOUNT_EXT 512

#define ITERS 100

int menu() {

    int choice;

    cout << "\n\t\tМеню\n"
    "1. Стандартный метод;\n"
    "2. Алгоритм Винограда;\n"
    "3. Оптимизированный п. 2;\n"
    "4. Алгоритм Штрассена;\n"

    "5. Замерить время;\n"
    "0. Выход.\n\n"
    "Выберете пункт (0-5): ";

    cin >> choice;
    wcout << endl;

    return choice;
}

int main() {

    int choice = menu();

    vector<Multiply*> muls{new Standard, new Vinograd, new VinogradOpt, new Strassen};

    while (choice) {

        bool mul = true;

        if (choice == 5) {
            timeMeasure(0, ITERS, MAX_AMOUNT_ORD);
            timeMeasure(1, ITERS, MAX_AMOUNT_ORD);
            timeMeasure(2, ITERS, MAX_AMOUNT_EXT);
        }
        else {
            MatrixT mtr1("../code/data/mtr1.txt");
            MatrixT mtr2("../code/data/mtr2.txt");

            if (mtr1.getColumns() * mtr1.getRows() * mtr2.getColumns() * mtr2.getRows() == 0) {
                cout << "Некорректный размер матрицы!" << endl;
            }
            else if (choice == 1) {

                if (mtr1.getColumns() != mtr2.getRows()) { 
                    cout << "Количество столбцов первой матрицы не совпадает с количеством строк второй!" << endl;
                    mul = false;
                }
            }
            else {
             
                if (!(mtr1.getRows() == mtr1.getColumns() && mtr2.getRows() == mtr2.getColumns() && mtr1.getRows() == mtr2.getColumns())) {
                    
                    if (choice != 4)
                        cout << "Методом Винограда можно умножать только квадратные матрицы!" << endl;
                    else    
                        cout << "Методом Штрассена можно умножать только квадратные матрицы, размер которых - степень 2!" << endl;

                    mul = false;
                }
                else {
                    
                    if (choice == 4 && ! isDegree(mtr1.getRows())) {
                        cout << "Методом Штрассена можно умножать только квадратные матрицы, размер которых - степень 2!" << endl;
                        mul = false;
                    }
                }
            }
            
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
