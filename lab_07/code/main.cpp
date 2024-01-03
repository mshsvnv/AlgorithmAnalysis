#include "measure.h"
#include "algs.h"

int menu() {
    std::cout << "\n\t\tМеню\n"
                 "1. Выполнить поиска подстроки в строке\n"
                 "    a) алгоритм Кнута-Морриса-Пратта;\n"
                 "    б) модифицированный КМП.\n"
                 "2. Подсчитать количество сравнений при выполнении поиска подстроки.\n"
                 "0. Выход.\n\n"
                 "Выберите опцию (0-2): ";

    int choice;
    
    cin >> choice;
    cout << std::endl;

    return choice;
}

int main()
{
    int choice = 0;

    while ((choice = menu())) {

        if (choice == 1) {

            string text, pattern;
            
            cout << "Введите исходную строку: ";
            cin >> ws;
            getline(cin, text);

            

            cout << "Введите исходную подстроку: ";
            cin >> ws;
            getline(cin, pattern);

            int res_01 = KMP(text, pattern);
            int res_02 = KMP_optimized(text, pattern);

            if (res_01 == -1 || res_02 == -1) 
                cout << "Исходная подстрока не найдена.\n";
            else {
                cout << "Смещение относительно начала (КМП): " << res_01 << "\n";
                cout << "Смещение относительно начала (КМП оптимизированный): " << res_02 << "\n";
            }
        }
        else if (choice == 2) {
            compMeasure();
            timeMeasure();
        }

    }
    return 0;
}