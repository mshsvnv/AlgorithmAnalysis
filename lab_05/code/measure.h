#pragma once

#include <iostream>
#include <ctime>

#include "conveyor.h"

double parallelMeasure(size_t req_cnt, size_t size);
double linearMeasure(size_t req_cnt, size_t size);
void timeMeasure1();
void timeMeasure2();