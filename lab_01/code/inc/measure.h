#pragma once

#include <iostream>
#include <chrono>

#include "algorithms.h"

wstring generateWord(int len);

auto getCPUTime(wstring& , wstring& , funcNotRecT);
auto getCPUTime(wstring& , wstring& , funcRecT);
auto getCPUTime(wstring& , wstring& , funcRecCashT);

void timeMeasure(int maxLen, int iters);