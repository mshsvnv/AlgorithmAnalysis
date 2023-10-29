#pragma once
#include <iomanip>

#include "multiply.h"

auto getCPUTime(MatrixT& , MatrixT& , Multiply*);
long long getThreadCpuTimeNs();
double getTotalTime(long long startT, long long endT);

void timeMeasure(int step, int iters, int maxAmount);

