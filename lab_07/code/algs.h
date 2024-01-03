#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

using func_ptr = int(*)(const string&, const string&);

void reset_comps();
pair<int, int> get_comp_amt();

vector<int> makePiList(const string& pattern);
unordered_map<char, int> makeBadCharsList(const string& pattern);

int KMP(const string& text, const string& pattern);
int KMP_optimized(const string& text, const string& pattern);