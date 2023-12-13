#include "../inc/sorts.h"

#include <thread>
#include <functional>

void print(arrayT& arr) {

    for (auto& elem: arr)
        cout << elem << " ";
    cout << endl;
}

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

    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, right);
}

void mergeSortMultiThread(arrayT& arr, int left, int right, int threads) {

	if (left >= right)
		return;

	int mid = (right + left) / 2;

	if (threads == 1) {
		thread t(std::bind(mergeSortMultiThread, ref(arr), left, mid, 0));
		mergeSortMultiThread(arr, mid + 1, right, 0);
		t.join();
	}
	else if (threads >= 2) {
		int oddThread = threads % 2;
		thread t1(std::bind(mergeSortMultiThread, ref(arr), left, mid, threads / 2 + oddThread));
		thread t2(std::bind(mergeSortMultiThread, ref(arr), mid + 1, right, threads / 2));
		t1.join();
		t2.join();
	}
	else {
		mergeSortMultiThread(arr, left, mid, 0);
		mergeSortMultiThread(arr, mid + 1, right, 0);
	}

	merge(arr, left, right);
}