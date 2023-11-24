#include <iostream>
#include <vector>
#include <thread>
#include "time.h"

using namespace std;

template<typename T>
using arrayT = vector<T>;

void calculatePart(const arrayT<double>& koefs, const int start, const int end, const double x, arrayT<double>& result) {
    for (int i = start; i <= end; ++i) {
        result[i] = koefs[i];

        if (i > start) {
            result[i] += x * result[i - 1];
        }
    }
}

int main() {
    srand(time(0));

    int power = 5;
    arrayT<double> koefs(power + 1);

    for (int i = 0; i <= power; ++i) {
        koefs[i] = rand() % 100 - 50;
        cout << "Коэффициента при x^" << power - i << ": " << koefs[i] << endl;
    }

    double tmp = 0;
    double x = 1;

    int num_threads = 3; // Количество потоков
    int step = (power + 1) / num_threads;

    arrayT<thread> threads(num_threads);
    arrayT<arrayT<double>> results(num_threads, arrayT<double>(power + 1, 0));

    for (int i = 0; i < num_threads; ++i) {
        int start = 2 * i * (step - 1);
        int end = (i == num_threads - 1) ? power : start + step - 1;
        cout << start << " " << end << endl;
        threads[i] = thread(calculatePart, ref(koefs), start, end, x, ref(results[i]));
    }

    for (int i = 0; i < num_threads; ++i) {
        threads[i].join();
    }

    for (int i = 0; i < num_threads; ++i) {
        for (int j = 0; j < power + 1; ++j)
            cout << results[i][j] << " ";
        cout << endl;
        int start = 2 * i * (step - 1);
        int end = (i == num_threads - 1) ? power : start + step - 1;
        tmp += results[i][end];
    }

    cout << "\nРезультат: " << tmp;
}