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

    int getRows() { return m_rows; }
    int getColumns() { return m_columns; }

    MatrixT copy(int begRow, int endRow, int begCol, int endCol);
    void merge(const MatrixT&, const MatrixT&, const MatrixT&, const MatrixT&);

    friend ostream& operator<<(ostream& out, const MatrixT& mtr);
    
    int& operator()(const int&, const int&);
    int operator()(const int&, const int&) const;
    
    MatrixT operator+(const MatrixT&);
    MatrixT operator-(const MatrixT&);

    void randomFill();

private:

    int m_rows, m_columns;
    vector<vector<int>> m_matrix; 
};