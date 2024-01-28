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