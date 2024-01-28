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