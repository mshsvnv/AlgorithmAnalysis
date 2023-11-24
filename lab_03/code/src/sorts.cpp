#include "../inc/sorts.h"

static void swap(int& left, int& right) {
    int tmp = left;
    left = right;
    right = tmp;
}

static int findMax(ArrayT& arr) {

    int max = arr[0], size = arr.size();

    for (int i = 1; i < size; i++) {

        if (arr[i] > max) 
            max = arr[i];
    }

    return max;
}

static int mod(int a, int b) {

    // return a % b;
    if (a >= 0)
        return a % b;
    else {
        while (a < 0)
            a += b;
        return a;
    }
}

ArrayT Radix::countSort(ArrayT& arr) {
    
    ArrayT ends(_base, 0);

    int size = arr.size();
    ArrayT arrNew(size);

    for (int i = 0; i < size; ++i) 
        // ends[mod(arr[i], _base)]++;
        ends[mod(arr[i], _base)]++;

    for (int i = 1; i < ends.size(); ++i)
        ends[i] += ends[i - 1];

    for (int i = 0; i < size; ++i) {
        // int& j = ends[mod(arr[i], _base)];
        int& j = ends[mod(arr[i], _base)];
        --j;
        arrNew[j] = arr[i];
    }

    return arrNew;
}

void Radix::execute(ArrayT& arr) {

    int size = arr.size();
    int maxElem = findMax(arr);

    ArrayT neg, pos;
    
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] < 0)
            neg.append(arr[i]);
        else
            pos.append(arr[i]);
    }

    _step = 10;
    _base = _step;

    while (maxElem) {
        pos = countSort(pos);
        neg = countSort(neg);

        _base *= _step;
    
        maxElem /= 10;
    }

    arr = neg + pos;
}

void Comb::execute(ArrayT& arr) {

    double koef = 1.247;
    int size = arr.size();

    int step = static_cast<int>(size / koef);

    while (step >= 1) {

        for (int i = 0; i + step < size; i++)

            if (arr[i] > arr[i + step])
                swap(arr[i], arr[i + step]);

        step = static_cast<int>(step / koef);
    }           
}

void Shell::execute(ArrayT& arr) {

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