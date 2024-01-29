#pragma once

# include <iostream>
# include <vector>
# include <memory>
# include <string>

using namespace std;

struct MatrixT {
    vector<vector<int>> arr;

    size_t n;
    size_t m;
};

struct MatrixCSR{
    vector<int> AN; // элементы
    vector<int> JA; // номер соотвествующего столбца для элемента
    vector<int> NR; // номер элемента в an начала следующей строки - размер N + 1, N - количество строк

    size_t n;
    size_t m;

    MatrixCSR() = default;
    MatrixCSR(size_t _n, size_t _m, size_t num_cnt);

    MatrixCSR operator+(const MatrixCSR &mtr);   
    MatrixT decomprass();
};

ostream& operator<<(ostream& stream, const MatrixCSR& mtr);
ostream& operator<<(ostream& stream, const MatrixT& mtr);
ostream& operator<<(ostream& stream, const vector<int>& vec);

void generate(MatrixCSR &a, size_t n, size_t m, size_t num_cnt);
MatrixCSR sum_mtr_csr(MatrixCSR &a, MatrixCSR &b);
// MatrixT decomprass(MatrixCSR &a);

// void print_mtr(MatrixT &mtr);
// void print_vector(std::vector<int> &arr);
// void print_mtr_csr(MatrixCSR &a);
