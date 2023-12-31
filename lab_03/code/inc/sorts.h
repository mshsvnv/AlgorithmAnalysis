#pragma once

#include <iostream>
#include "array.h"

using namespace std;

class Sort {
public:
    virtual ~Sort() = default;

    virtual void execute(ArrayT& arr) = 0;
    virtual int getVolume(int) = 0;
};

class Radix : public Sort {
    int _base;
    int _step;
public:
    void execute(ArrayT& arr) override;
    ArrayT countSort(ArrayT& arr);
    int getVolume(int);
};

class Comb : public Sort {
public:
    void execute(ArrayT& arr) override;
    int getVolume(int);
};

class Shell : public Sort {
public:
    void execute(ArrayT& arr) override;
    int getVolume(int);
};