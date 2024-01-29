#pragma once 

#include <queue>
#include <thread>
#include <mutex>
#include <algorithm>
#include <string>
#include <ctime>
#include <fstream>

#include "matrix.h"
#include "read.h"

struct requestT {
    MatrixCSR mtr_a;
    MatrixCSR mtr_b;
    MatrixCSR mtr_c;
    MatrixT result;

    timespec p1_start;
    timespec p1_end;
    timespec p2_start;
    timespec p2_end;
    timespec p3_start;
    timespec p3_end;
};

#define MAX_REQUEST 100
#define MATRIX_SIZE 10
#define LOOPS 100

struct PoolResultT {

    PoolResultT()=default;
    bool operator < (const PoolResultT &other) const {
        return this->nanosec < other.nanosec;
    }

    PoolResultT &operator = (const PoolResultT &other) {
        this->message = other.message;
        this->nanosec = other.nanosec;
        return *this;
    }

    long long nanosec;
    string message;
};

void packData(size_t n, size_t m, size_t cnt, requestT *r);

void linear();
void parallel();

void thread_1(size_t req_cnt, size_t n, size_t m, size_t cnt, queue<requestT *> &q1);
void thread_2(int req_cnt, queue<requestT *> &q1, queue<requestT *> &q2);
void thread_3(int req_cnt, queue<requestT *> &q2, vector<requestT *> &pool);

void printPool(vector<requestT *> &pool, const string &filename);