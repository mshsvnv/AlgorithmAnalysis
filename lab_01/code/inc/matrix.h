#pragma once

#include <iostream>

using namespace std;

// void freeMtr(int** mtr, int m);
// int** allocateMtr(int m, int n);

void allocateMtr(int*** mtr, int m, int n);

void freeMtr(int*** mtr, int m);

void printMtr(wstring& word1, wstring& word2, int*** mtr);
