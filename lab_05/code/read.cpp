#include "read.h"

int getRequestNumber() {

    cout << "Введите количество заявок (больше 0): ";

    int n = 0;

    while (scanf("%d", &n) != 1 || n < 1)
        cout << "Повторите попытку: ";

    char ch = 1;
    while (ch != '\n')
        scanf("%c", &ch);
    return n;
}

int getMatrixNum() {

    cout << "Введите количество элементов (больше 0): ";
    int n = 0;

    while (scanf("%d", &n) != 1 || n < 1)
        cout << "Повторите попытку: ";

    char ch = 1;
    while (ch != '\n')
        scanf("%c", &ch);
    return n;
}

int getMatrixN() {

    cout << "Введите количество строк n (больше 0): ";
    int n = 0;

    while (scanf("%d", &n) != 1 || n < 1)
        cout << "Повторите попытку: ";

    char ch = 1;
    while (ch != '\n')
        scanf("%c", &ch);
    return n;
}

int getMatrixM() {

    cout << "Введите количество столбцов m (больше 0): ";
    int n = 0;
    
    while (scanf("%d", &n) != 1 || n < 1)
        cout << "Повторите попытку: ";

    char ch = 1;
    while (ch != '\n')
        scanf("%c", &ch);
    return n;
}