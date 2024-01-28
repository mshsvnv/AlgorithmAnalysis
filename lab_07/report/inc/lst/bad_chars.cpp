unordered_map<char, int> makeBadCharsList(const string& pattern) {
    int n = pattern.length();
    unordered_map<char, int> badChars;
    
    for (int i = 0; i < n; ++i)
        badChars[pattern[i]] = n - i - 1;
    return badChars;
}