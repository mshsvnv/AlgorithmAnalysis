#pragma once

#include <iostream>

using namespace std;

void freeMtr(int** mtr, int m);
int** allocateMtr(int m, int n);
void printMtr(int** mtr, wstring& word1, wstring& word2);
