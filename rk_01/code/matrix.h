#pragma once

# include <iostream>
# include <vector>
# include <memory>
# include <string>

using namespace std;

struct MatrixCSR{
    vector<int> AN; // элементы
    vector<int> JA; // номер соотвествующего столбца для элемента
    vector<int> NR; // номер элемента в an начала следующей строки - размер N + 1, N - количество строк

    size_t n;
    size_t m;

    MatrixCSR() = default;
    MatrixCSR(size_t _n, size_t _m, size_t num_cnt);

    MatrixCSR operator+(const MatrixCSR &mtr); 
};

ostream& operator<<(ostream& stream, const MatrixCSR& mtr);
ostream& operator<<(ostream& stream, const vector<int>& vec);