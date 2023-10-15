#pragma once

#include <iostream>
#include <ctime>

#include "algorithms.h"

wstring generateWord(int len);

auto getCPUTime(wstring& , wstring& , Algs::funcT);
auto getCPUTime(wstring& , wstring& , Algs::funcRecT);

void timeMeasure(int maxLen, int iters);