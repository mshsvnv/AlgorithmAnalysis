void mergeSortMultiThread(std::vector<int>& nums, int s, int e, int availThreads)
{
	if (s >= e)
	{
		return;
	}

	int mid = (s + e) / 2;
	if (availThreads == 1)
	{
		std::thread t(std::bind(mergeSortMultiThread, std::ref(nums), s, mid, 0));
		mergeSortMultiThread(nums, mid + 1, e, 0);
		t.join();
	}
	else if (availThreads >= 2)
	{
		int oddThread = (availThreads % 2);
		std::thread t1(std::bind(mergeSortMultiThread, std::ref(nums), s, mid, availThreads / 2 + oddThread));
		std::thread t2(std::bind(mergeSortMultiThread, std::ref(nums), mid + 1, e, availThreads / 2));
		t1.join();
		t2.join();
	}
	else
	{
		mergeSortMultiThread(nums, s, mid, 0);
		mergeSortMultiThread(nums, mid + 1, e, 0);
	}
	merge(nums, s, mid, e);
}
