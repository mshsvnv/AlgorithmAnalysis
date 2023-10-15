#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

#include "matrix.h"

using namespace std;

namespace Algs {
    using funcT = int(*)(wstring&, wstring&, bool);
    using funcRecT = int(*)(wstring&, wstring&, int, int);

    int notRecursiveLev(wstring &word1, wstring &word2, bool print = false);
    int notRecursiveDamLev(wstring& word1, wstring& word2, bool print = false);
    int recursive(wstring& word1, wstring& word2, int ind1, int ind2);
    int recursiveCash_Decor(wstring& word1, wstring& word2, bool print = false);
    int recursiveCash(wstring& word1, wstring& word2, int ind1, int ind2, int** dict);
}