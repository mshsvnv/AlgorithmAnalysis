void merge(std::vector<int>& nums, int s, int mid, int e)
{
	std::vector<int> lnums, rnums;
	for (int i = s; i <= e; i++)
	{
		if (i <= mid)
		{
			lnums.push_back(nums[i]);
		}
		else
		{
			rnums.push_back(nums[i]);
		}
	}

	int l = 0, r = 0, k = s;

	while (l < lnums.size() && r < rnums.size())
	{
		if (lnums[l] < rnums[r])
		{
			nums[k++] = lnums[l++];
		}
		else
		{
			nums[k++] = rnums[r++];
		}
	}

	while (l < lnums.size())
	{
		nums[k++] = lnums[l++];
	}
	while (r < rnums.size())
	{
		nums[k++] = rnums[r++];
	}
}