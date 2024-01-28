#include "./inc/sorts.h"
#include "./inc/measure.h"

int menu() {

    int choice;

    cout << "\n\t\tМеню\n"
    "1. Обычная сортировка слиянием\n"
    "2. Расспаралл. сортировка слиянием\n\n"
    "3. Замерить время\n"
    "0. Выход\n\n"
    "Выберете пункт (0-4): ";

    cin >> choice;
    cout << endl;

    return choice;
}

int main() {

    int choice = menu();

    while (choice) {

        if (choice == 3) {

            int start = 10000, stop = 10001, step = 1;
			int count = 100;
			int startThread = 0, stopThread = 48;

			cout << "Введите начальный размер массива, конечный размер и шаг изменения размера массива\n";
			cin >> start >> stop >> step;
			cout << "Введите количество повторений сортировки: ";
			cin >> count;
			cout << "Введите начальное число потоков массива, конечное число потоков\n";
			cin >> startThread >> stopThread;
            
			getTimeResults(start, stop, step, count, startThread, stopThread, 2);

            start = 1000, stop = 10000, step = 1000, startThread = 1, stopThread = 2;

            getTimeResults(start, stop, step, count, startThread, stopThread, 1);
        }
        else {

            arrayT arr;

            int len;
            cout << "Длина массива: ";
            cin >> len;

            for (int i = 0; i < len; ++i) {
                int elem;
                cin >> elem;
                arr.emplace_back(elem);
            }

            cout << "До: ";
            print(arr);

            if (choice == 1)
                mergeSort(arr, 0, len);
            else {
                int n;

                cout << "Количество потоков: ";
                cin >> n;

                mergeSortMultiThread(arr, 0, len, n);
            }

            cout << "После: ";
            print(arr);
        }

        choice = menu();
    }
}