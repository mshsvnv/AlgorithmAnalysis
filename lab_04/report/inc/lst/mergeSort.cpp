void mergeSort(arrayT& arr, int left, int right) {

    if (right <= left)
        return;

    int mid = (right + left) / 2;

    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, right);
}