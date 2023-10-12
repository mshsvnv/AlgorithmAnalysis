#include "../inc/sorts.h"

static void swap(int& left, int& right) {
    int tmp = left;
    left = right;
    right = tmp;
}

void Radix::execute(arrayT& arr) {

}

void Comb::execute(arrayT& arr) {

    double koef = 1.247;

    int step = static_cast<int>(arr.size() / koef);
    int buf;

    while (step >= 1) {

        for (int i = 0; i + step < arr.size(); i++)

            if (arr[i] > arr[i + step])
                swap(arr[i], arr[i + step]);

        step = static_cast<int>(step / koef);
    }           
}

void Shell::execute(arrayT& arr) {

    // double step = arr.size() / 2;

    // for (int i = step; step > 0; step /= 2) {

    //     for (int j = i; j < arr.size(); ++j) {

    //         int temp = arr[j];

    //         for (int k = j; k )

    //     }
    // }

}