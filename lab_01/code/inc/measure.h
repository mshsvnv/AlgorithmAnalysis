#pragma once

#include <iostream>

#include "algorithms.h"

wstring generateWord(int len);

double getCPUTime(wstring& , wstring& , funcNotRecT);
double getCPUTime(wstring& , wstring& , funcRecT);
double getCPUTime(wstring& , wstring& , funcRecCashT);

void timeMeasure(int maxLen, int iters);

int getNotRecursiveLev(int len);
int getNotRecursiveDamLev(int len);
int getRecursiveDam(int len);
int getRecursiveDamCash(int len);

void memoryMeasure(int maxLen, int step);