#include <iostream>
#include <vector>

using namespace std;

using arrayT = vector<int>;

void merge(arrayT& arr, int left, int right) {

    int mid = (left + right) / 2;

    int i = left, 
        j = mid + 1, pos = 0, 
        len = right - left + 1;

    arrayT tmp(len);

    while (i <= mid && j <= right)
        tmp[pos++] = (arr[i] < arr[j]) ? arr[i++] : arr[j++];

    while (i <= mid)    
        tmp[pos++] = arr[i++];

    while (j <= right)    
        tmp[pos++] = arr[j++];

    for (int i = left; i <= right; ++i)
        arr[i] = tmp[i - left];
}

void mergeSort(arrayT& arr, int left, int right) {

    if (right <= left)
        return;

    int mid = (right + left) / 2;

    cout << left << mid << right << endl;

    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, right);
}

int main() {

    arrayT arr{5, 4, 3, -22, -11};

    mergeSort(arr, 0, 4);

    for (auto elem : arr)
        cout << elem << " ";
    cout << endl;
}