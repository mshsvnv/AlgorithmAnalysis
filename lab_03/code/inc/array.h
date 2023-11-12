#pragma once

#include <iostream>
#include <fstream>
#include <sstream>

#include <vector>
#include <string>

using namespace std;

class ArrayT {
public:
    ArrayT() = default;
    ArrayT(int len, int num = 0);
    ArrayT(const char* fileName);

    friend ostream& operator<<(ostream& out, const ArrayT&);
    
    int& operator[](int ind);
    int operator[](int ind) const;
    ArrayT operator+(const ArrayT& other);

    void randomFill();
    void ascFill();
    void descFill();

    int size() const { return _arr.size(); }
    void append(int num) { _arr.emplace_back(num); }

private:
    vector<int> _arr;
};