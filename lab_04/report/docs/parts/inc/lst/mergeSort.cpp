void mergeSort(std::vector<int>& arr, int left, int right)
{
	if (left >= right)
	{
		return;
	}
	int mid = (left + right) / 2;
	mergeSort(arr, left, mid);
	mergeSort(arr, mid + 1, right);

	merge(arr, left, mid, right);
}