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