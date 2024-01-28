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