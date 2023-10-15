#include "../inc/sorts.h"

static void swap(int& left, int& right) {
    int tmp = left;
    left = right;
    right = tmp;
}

static int findMax(arrayT& arr) {

    int max = arr[0], size = arr.size();

    for (int i = 1; i < size; i++) {

        if (arr[i] > max) 
            max = arr[i];

    }

    return max;
}

arrayT Radix::countSort(arrayT& arr) {
    
    static int base = 10;
    int step = 10;
    vector<int> ends(10, 0);

    int size = arr.size();
    arrayT arrNew;
    arrNew.resize(size);

    for (int i = 0; i < size; ++i)
        ends[arr[i] % base]++;

    for (int i = 1; i < ends.size(); ++i)
        ends[i] += ends[i - 1];

    for (int i = 0; i < size; ++i) {

        int& j = ends[arr[i] % base];
        --j;
        arrNew[j] = arr[i];

    }

    base *= step;

    for (auto elem : ends) 
        cout << elem << " ";
    cout << endl;

    return arrNew;
}

void Radix::execute(arrayT& arr) {

    int size = arr.size();
    int maxElem = findMax(arr);

    while (maxElem) {
        arr = countSort(arr);
        maxElem /= 10;
    }
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

    int size = arr.size();
    int gap = size / 2;

    for (int n = gap; n > 0; n /= 2) {

        for (int i = 1; i < size; i += n) {

            for (int j = i; j >= 1; --j) {

                if (arr[j - 1] > arr[j])
                    swap(arr[j - 1], arr[j]);
            }
        }

    }
}