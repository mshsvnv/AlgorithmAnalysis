#include "matrix.h"

int main() {

    srand(time(0));

    auto a = MatrixCSR(5, 5, 3);
    auto b = MatrixCSR(5, 5, 3);

    auto c = a + b;
    cout << "A:\n" << a << endl;
    cout << "B:\n" << b << endl;
    cout << "Итоговая матрица C:\n" << c << endl;
}