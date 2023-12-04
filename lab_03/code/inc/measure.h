#pragma once
#include <iomanip>

#include "sorts.h"

auto getCPUTime(Sort*, ArrayT&);
long long getThreadCpuTimeNs();
double getTotalTime(long long startT, long long endT);

void timeMeasure(int step, int iters, int maxAmount, int type);
void memoryMeasure(int step, int maxAmount);
    