#include "../inc/algorithms.h"

int notRecursiveLev(wstring &word1, wstring &word2, int*** mtr) {
    
    int len1 = word1.length();
    int len2 = word2.length();

    for (int i = 0; i <= len2; ++i) {

        for (int j = 0; j <= len1; ++j) {

            if (i == 0)
                (*mtr)[i][j] = j;
            else if (j == 0)
                (*mtr)[i][j] = i;
            else {
                int dif = (word1[j - 1] == word2[i - 1]) ? 0 : 1;

                (*mtr)[i][j] = min((*mtr)[i - 1][j] + 1, 
                               min((*mtr)[i][j - 1] + 1, (*mtr)[i - 1][j - 1] + dif) 
                               );
            }
        }
    }

   return (*mtr)[len2][len1];
}

int notRecursiveDamLev(wstring &word1, wstring &word2, int*** mtr) {

    int len1 = word1.length();
    int len2 = word2.length();

    for (int i = 0; i <= len2; ++i) {

        for (int j = 0; j <= len1; ++j) {

            if (i == 0)
                (*mtr)[i][j] = j;
            else if (j == 0)
                (*mtr)[i][j] = i;
            else {
                int dif = (word1[j - 1] == word2[i - 1]) ? 0 : 1;

                (*mtr)[i][j] = min((*mtr)[i - 1][j] + 1, 
                                    min((*mtr)[i][j - 1] + 1, (*mtr)[i - 1][j - 1] + dif));

                if (word1[j - 2] == word2[i - 1] && word1[j - 1] == word2[i - 2]) 
                    (*mtr)[i][j] = min((*mtr)[i][j], (*mtr)[i - 2][j - 2] + 1);
            }
        }
    }

    return (*mtr)[len2][len1];
}

int recursive(wstring &word1, wstring &word2, int ind1, int ind2) {

    if (min(ind1, ind2) == 0)
        return max(ind1, ind2);

    int dif = (word1[ind1 - 1] == word2[ind2 - 1]) ? 0 : 1;

    int res = min(recursive(word1, word2, ind1 - 1, ind2 - 1) + dif,
                  min(recursive(word1, word2, ind1 - 1, ind2) + 1, 
                      recursive(word1, word2, ind1, ind2 - 1) + 1));

    if (word1[ind1 - 1] == word2[ind2 - 2] && word1[ind1 - 2] == word2[ind2 - 1])
        res = min(res, recursive(word1, word2, ind1 - 2, ind2 - 2) + 1);

    return res;
}

int recursiveCash(wstring &word1, wstring &word2, int ind1, int ind2, mapT& dict) {

    if (min(ind1, ind2) == 0)
        return max(ind1, ind2);
    
    wstring key = to_wstring(ind1) + L":" + to_wstring(ind2);

    if (dict[key])
        return dict[key];

    int dif = (word1[ind1 - 1] == word2[ind2 - 1]) ? 0 : 1;

    dict[key] = min(recursiveCash(word1, word2, ind1 - 1, ind2 - 1, dict) + dif,
                    min(recursiveCash(word1, word2, ind1 - 1, ind2, dict) + 1, 
                        recursiveCash(word1, word2, ind1, ind2 - 1, dict) + 1));

    if (word1[ind1 - 1] == word2[ind2 - 2] && word1[ind1 - 2] == word2[ind2 - 1])
        dict[key] = min(dict[key], recursiveCash(word1, word2, ind1 - 2, ind2 - 2, dict) + 1);

    return dict[key];
}