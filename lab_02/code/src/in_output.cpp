#include "../inc/in_output.h"

int readMtr(matrixT& mtr, bool square) {

    int a, b;

    int rc = readSize(a, b, square);

    if (rc) {
        cout << "Неверное значение!";

        return 1;
    }

    if (square && a != b) {
        cout << "Матрица должна быть прямоугольной!";

        return 1;
    }

    arrayT arr;
    arr.resize(a, 0);
    mtr.resize(b, arr);
    
    cout << "Элементы матрицы: ";

    for (int i = 0; i < a; ++i) {
        for (int j = 0; j < b; ++j) {

            if (!(cin >> mtr[i][j])) {
                cout << "Неверное значение элемента!";

                return 1;
            }
        }
    }
    
    return 0;
}

int readSize(int& a,int& b, bool square) {

    cout << "Размер матрицы: ";
    char sym;

    return (!(cin >> a >> sym >> b) || a <= 0 || b <= 0) ? 1 : 0;
}


void printMtr(matrixT& mtr) {

    for (const auto& row : mtr) {

        for (const auto& elem : row)
            cout << elem << " ";
        cout << endl;
    }
}
