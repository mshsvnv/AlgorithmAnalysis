#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

class MatrixT {
public:
    MatrixT() = default;
    MatrixT(int, int);
    MatrixT(const char* fileName);

    friend ostream& operator<<(ostream& out, const MatrixT& mtr);

    int& operator()(const int&, const int&);

    void randomFill();

    int m_rows, m_columns;
    vector<vector<int>> m_matrix; 
};