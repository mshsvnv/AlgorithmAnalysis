#pragma once

#include "matrix.h"

class Multiply {
public:
    virtual ~Multiply() = default;

    virtual MatrixT multiply(MatrixT& m1, MatrixT& m2) = 0;
};

class Standard : public Multiply {
public:
    MatrixT multiply(MatrixT& m1, MatrixT& m2) override;
};

class Vinograd : public Multiply {
public:
    MatrixT multiply(MatrixT& m1, MatrixT& m2) override;
};

class VinogradOpt : public Multiply {
public:
    MatrixT multiply(MatrixT& m1, MatrixT& m2) override;
};