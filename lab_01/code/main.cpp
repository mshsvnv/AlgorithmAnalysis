#include <fcntl.h>
// #include <io.h>

#include "inc/algorithms.h"
#include "inc/measure.h"

#define MAX_LEN 100
#define STEP 10
#define MAX_ITER 1000

int menu() {

    int choice;

    wcout << L"\n\t\tМеню\n"
    "1. Запуск алгоритмов поиска расстояния Левенштейна:\n"
    "   1) Нерекурсивный Левенштейна;\n" 
    "   2) Нерекурсивный Дамерау-Левенштейна;\n"
    "   3) Рекурсивный Дамерау-Левенштейна без кэша;\n"
    "   4) Рекурсивный Дамерау-Левенштейна с кэшом;\n"
    "2. Замерить время для реализованных алгоритмов;\n"
    "0. Выход\n\n"
    "Выберете пункт (0-2): ";

    wcin >> choice;
    wcout << endl;

    return choice;
}

int main() {

    std::setlocale(LC_ALL, "ru_RU.UTF-8");
    // _setmode(_fileno(stdout), _O_U16TEXT);
    // _setmode(_fileno(stdin), _O_U16TEXT);


    wstring word1, word2;

    int choice = menu();
    int res = 0, m, n;

    while (choice) {

        if (choice == 1) {

            wcout << L"Введите 1е слово: ";
            wcin >> word1;

            wcout << L"Введите 2е слово: ";
            wcin >> word2;
            wcout << endl;

            m = word1.length();
            n = word2.length();

            wcout << L"Минимальное кол-во операций:\n";
            res = Algs::notRecursiveLev(word1, word2, true);
            wcout << L"   1) Нерекурсивный Левенштейна:                " << res << endl;

            res = Algs::notRecursiveDamLev(word1, word2, true);
            wcout << L"   2) Нерекурсивный Дамерау-Левенштейна:        " << res << endl;

            res = Algs::recursive(word1, word2, m, n);
            wcout << L"   3) Рекурсивный Дамерау-Левенштейна без кэша: " << res << endl ;
            
            res = Algs::recursiveCash_Decor(word1, word2, true);
            wcout << L"   4) Рекурсивный Дамерау-Левенштейна с кэшом:  " << res << endl;

        }
        else if (choice == 2) 
            timeMeasure(200, 1000);
        else
            wcout << L"Завершение!\n";

        choice = menu();
    }
}