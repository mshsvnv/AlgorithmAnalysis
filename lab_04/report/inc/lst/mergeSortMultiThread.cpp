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