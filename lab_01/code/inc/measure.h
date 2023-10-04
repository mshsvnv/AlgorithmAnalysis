#pragma once

#include <iostream>
#include <chrono>

#include "algorithms.h"

wstring generateWord(int len);

auto getCPUTime(wstring& , wstring& , funcNotRecT);
auto getCPUTime(wstring& , wstring& , funcRecT);
auto getCPUTime(wstring& , wstring& , funcRecCashT);

void timeMeasure(int maxLen, int iters);

int getNotRecursiveLev(int len);
int getNotRecursiveDamLev(int len);
int getRecursiveDam(int len);
int getRecursiveDamCash(int len);

void memoryMeasure(int maxLen, int step);