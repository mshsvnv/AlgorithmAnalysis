#pragma once

#include <iostream>
#include <vector>

#include "semaphore.h"

using namespace std;
using arrayT = vector<int>;

void print(arrayT& arr);
void mergeSort(arrayT& arr, int left, int right);
void mergeSortMultiThread(arrayT& arr, int left, int right, int threads);