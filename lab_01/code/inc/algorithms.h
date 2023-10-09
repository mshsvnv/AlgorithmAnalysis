#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

#include "matrix.h"

using namespace std;

using mapT = unordered_map<int, int>;

using funcNotRecT = int(*)(wstring&, wstring&, bool);
using funcRecT = int(*)(wstring&, wstring&, int, int);
using funcRecCashT = int(*)(wstring&, wstring&, int, int, mapT&);

int notRecursiveLev(wstring &word1, wstring &word2, bool print = false);
int notRecursiveDamLev(wstring& word1, wstring& word2, bool print = false);

int recursive(wstring& word1, wstring& word2, int ind1, int ind2);

int recursiveCash(wstring& word1, wstring& word2, int ind1, int ind2, mapT& dict);
