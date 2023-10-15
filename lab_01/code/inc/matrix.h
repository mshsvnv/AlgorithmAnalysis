#pragma once

#include <iostream>

using namespace std;

namespace Matrix {
    void release(int** mtr, int rows);
    int** allocate(int rows, int columns, bool fill = false);
    void print(int** mtr, wstring& word1, wstring& word2);
}