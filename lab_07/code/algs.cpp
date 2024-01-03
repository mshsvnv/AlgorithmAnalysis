#include "algs.h"

static std::pair<int, int> comps{};

void reset_comps() {
    comps = {0, 0};
}

pair<int, int> get_comp_amt() {
    return comps;
}

vector<int> makePiList(const string& pattern) {

    int n = pattern.length();
    vector pi(n, 0);

    int j = 0, i = 1;

    while (i < n) {

        if (pattern[j] == pattern[i]) {
            pi[i] = j + 1;
            j++, i++;
        } else {
            if (j) 
                j = pi[j - 1];
            else {
                pi[j] = 0;
                i++;
            }
        }
    }

    return pi;
}

unordered_map<char, int> makeBadCharsList(const string& pattern) {
    int n = pattern.length();
    unordered_map<char, int> badChars;
    
    for (int i = 0; i < n; ++i)
        badChars[pattern[i]] = n - i - 1;
    return badChars;
}

int KMP(const string& text, const string& pattern) {

    int m = pattern.length();
    int n = text.length();

    vector<int> pi = makePiList(pattern);

    int i = 0, j = 0;

    ++comps.first;
    while (i < n) {

        ++comps.first;
        if (text[i] == pattern[j]) {
            
            i++, j++;

            ++comps.first;
            if (j == m) 
                return i - m;
            
        } else {
            ++comps.first;

            if (j == 0) {
                i++;
            }
            else 
                j = pi[j - 1];
        }
        ++comps.first;
    }

    return -1;
}

int KMP_optimized(const string& text, const string& pattern) {
    
    int m = pattern.length();
    int n = text.length();

    vector<int> pi = makePiList(pattern);
    unordered_map<char, int> badChars = makeBadCharsList(pattern);

    int shift = 0;

    ++comps.second;
    while (shift <= n - m) {

        int j = m - 1;

        ++comps.second;
        while (j >= 0 && pattern[j] == text[shift + j])
            j--;

        ++comps.second;
        if (j < 0)
            return shift;
        else {
            int k = m;

            ++comps.second;
            if (badChars.contains(text[shift + j]))
                k = badChars[text[shift + j]];

            shift += max(pi[j], k);
        }

        ++comps.second;
    }
    
    return -1;
}