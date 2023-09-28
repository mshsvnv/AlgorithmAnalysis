#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

#include "matrix.h"

using namespace std;

using mapT = map<wstring, int>;

using funcNotRecT = int(*)(wstring&, wstring&, int***);
using funcRecT = int(*)(wstring&, wstring&, int, int);
using funcRecCashT = int(*)(wstring&, wstring&, int, int, mapT&);

int notRecursiveLev(wstring &word1, wstring &word2, int*** mtr);
int notRecursiveDamLev(wstring& word1, wstring& word2, int*** mtr);

int recursive(wstring& word1, wstring& word2, int ind1, int ind2);

int recursiveCash(wstring& word1, wstring& word2, int ind1, int ind2, mapT& dict);
