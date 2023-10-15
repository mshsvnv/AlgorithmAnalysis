#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using arrayT = vector<int>;

class Sort {
public:
    virtual ~Sort() = default;

    virtual void execute(arrayT& arr) = 0;
};

class Radix : public Sort {
public:
    void execute(arrayT& arr) override;
    arrayT countSort(arrayT& arr);
};

class Comb : public Sort {
public:
    void execute(arrayT& arr) override;
};

class Shell : public Sort {
public:
    void execute(arrayT& arr) override;
};