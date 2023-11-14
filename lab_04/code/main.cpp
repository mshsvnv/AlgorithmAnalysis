#include <iostream>
#include <vector>

using namespace std;

using arrayT = vector<int>;

void merge(arrayT& arr, int left, int right) {

    int mid = (left + right) / 2;

    int i = left, 
        j = mid, pos = 0, 
        len = right - left;

    arrayT tmp(len);

    while (i <= mid || j <= right)
        tmp[pos++] = (arr[i] < arr[j]) ? arr[i++] : arr[j++];
    
    // while (i <= mid)

    for (int i = 0; i < len; ++i)
        arr[left + i] = tmp[i];
}

void mergeSort(arrayT& arr, int left, int right) {

    if (right <= left)
        return;

    int mid = (right + left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid, right);
    merge(arr, left, right);
}

int main() {

    arrayT arr{1, 2, 3, 4, 5};
    mergeSort(arr, 0, 5);

    for (auto elem : arr)
        cout << elem << " ";
    cout << endl;
}