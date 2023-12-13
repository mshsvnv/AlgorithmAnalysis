#include "../inc/measure.h"

#include <random>
#include <ctime>

const double TIMEDIVISION = 1e6; //Millisecounds
const int MAXVAL = 1e4;

arrayT  generateVector(const size_t len) {
	srand(time(NULL));
	arrayT vec(len);

	random_device dev;
	mt19937 rng(dev());
	uniform_int_distribution<std::mt19937::result_type> dist(0, 1e7);

	for (size_t i = 0; i < len; i++)
		vec[i] = dist(rng);

	return vec;
}

long getCpuTime() {
	return std::clock();
}

double getCPUTimeMerge(arrayT& vec)
{
	clock_t startTime;
	clock_t endTime;

	startTime = getCpuTime();
	mergeSort(vec, 0, vec.size() - 1);
	endTime = getCpuTime();

	return  (double)(endTime - startTime) / (CLOCKS_PER_SEC) * 1e3;
}

double getCPUTimeMergeMultiThread(arrayT& vec, int threadCount)
{

	clock_t startTime;
	clock_t endTime;

	startTime = getCpuTime();
	mergeSortMultiThread(vec, 0, vec.size() - 1, threadCount);
	endTime = getCpuTime();

	return  (double)(endTime - startTime) / (CLOCKS_PER_SEC) * 1e3;
}

double getTimeResultsMatrix(size_t wordsLen,
                            int countProcessed,
                            arrayT& result,
                            int threadCount,
                            double mergeTimePrev)
{

	arrayT vec(wordsLen);

	for (size_t i = 0; i < wordsLen; i++)
		vec[i] = result[i];

	double mergeSortTime = 0.0;
	double mergeSortTimeMultiThread = 0.0;

	for (int i = 0; i < countProcessed; ++i) {
		arrayT vec_test = vec;
		if (mergeTimePrev < 0.0)
			mergeSortTime += getCPUTimeMerge(vec_test);
		vec_test = vec;
		mergeSortTimeMultiThread += getCPUTimeMergeMultiThread(vec_test, threadCount);

	}

	if (mergeTimePrev < 0.0)
		mergeSortTime /= countProcessed;
	else
		mergeSortTime = mergeTimePrev;

	mergeSortTimeMultiThread /= countProcessed;

	printf("|%7zu||%15.5g||%18.5g|%3d|\n", wordsLen, mergeSortTime, mergeSortTimeMultiThread, threadCount);
	std::cout << std::flush;
	return mergeSortTime;
}

void getTimeResults(size_t wordLenStart,
                    size_t wordLenStop,
                    size_t wordLenStep,
                    int countProcessed,
                    int threadCountStart,
                    int threadCountEnd)
{
	printf("\n\n|   n   ||   Сортировка слиянием(мс)    ||   Сортировка Слияние многопоток(мс)    ||  число потоков|\n");
	arrayT res = generateVector(wordLenStop);
	double prevTime;

	for (size_t i = wordLenStart; i < wordLenStop; i += wordLenStep)
	{
		prevTime = -1.0;
		for (int thr = threadCountStart; thr < threadCountEnd; ++thr)
			prevTime = getTimeResultsMatrix(i, countProcessed, res, thr, prevTime);

	}
}