#pragma once
#include <ctime>

#include "algs.h"

auto getCPUTime(func_ptr, const string&, const string&);
long long getThreadCpuTimeNs();
double getTotalTime(long long startT, long long endT);

void timeMeasure();
void compMeasure();
    