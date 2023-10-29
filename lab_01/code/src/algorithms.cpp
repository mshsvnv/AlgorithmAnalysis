#include "../inc/algorithms.h"

int Algs::notRecursiveLev(wstring &word1, wstring &word2, bool print) {
    
    int len1 = word1.length();
    int len2 = word2.length();

    int** mtr = Matrix::allocate(len2 + 1, len1 + 1);

    if (!mtr)
        return 0;

    for (int i = 0; i <= len2; ++i) {

        for (int j = 0; j <= len1; ++j) {

            if (i == 0)
                mtr[i][j] = j;
            else if (j == 0)
                mtr[i][j] = i;
            else {
                int dif = (word1[j - 1] == word2[i - 1]) ? 0 : 1;

                mtr[i][j] = min(mtr[i - 1][j] + 1, 
                               min(mtr[i][j - 1] + 1, mtr[i - 1][j - 1] + dif));
            }
        }
    }

    if (print)  
        Matrix::print(mtr, word1, word2);

    int res = mtr[len2][len1];
    Matrix::release(mtr, len2 + 1);

    return res;
}

int Algs::notRecursiveDamLev(wstring &word1, wstring &word2, bool print) {

    int len1 = word1.length();
    int len2 = word2.length();

    int** mtr = Matrix::allocate(len2 + 1, len1 + 1);

    if (!mtr)
        return 0;

    for (int i = 0; i <= len2; ++i) {

        for (int j = 0; j <= len1; ++j) {

            if (i == 0)
                mtr[i][j] = j;
            else if (j == 0)
                mtr[i][j] = i;
            else {
                int dif = (word1[j - 1] == word2[i - 1]) ? 0 : 1;

                mtr[i][j] = min(mtr[i - 1][j] + 1, 
                                min(mtr[i][j - 1] + 1, mtr[i - 1][j - 1] + dif));

                if (i > 1 && j > 1 && word1[j - 2] == word2[i - 1] && word1[j - 1] == word2[i - 2]) 
                    mtr[i][j] = min(mtr[i][j], mtr[i - 2][j - 2] + 1);
            }
        }
    }

    if (print)  
        Matrix::print(mtr, word1, word2);

    int res = mtr[len2][len1];
    Matrix::release(mtr, len2 + 1);

    return res;
}

int Algs::recursive(wstring &word1, wstring &word2, int ind1, int ind2) {

    if (min(ind1, ind2) == 0)
        return max(ind1, ind2);

    int dif = (word1[ind1 - 1] == word2[ind2 - 1]) ? 0 : 1;

    int res = min(recursive(word1, word2, ind1 - 1, ind2 - 1) + dif,
                  min(recursive(word1, word2, ind1 - 1, ind2) + 1, 
                      recursive(word1, word2, ind1, ind2 - 1) + 1));

    if (ind1 > 1 && ind2 > 1 && word1[ind1 - 1] == word2[ind2 - 2] && word1[ind1 - 2] == word2[ind2 - 1])
        res = min(res, recursive(word1, word2, ind1 - 2, ind2 - 2) + 1);

    return res;
}

int Algs::recursiveCash_Decor(wstring& word1, wstring& word2, bool print) {

    int len1 = word1.length();
    int len2 = word2.length();

    int** cash = Matrix::allocate(len2 + 1, len1 + 1, true);

    if (!cash)
        return 0;

    int res = recursiveCash(word1, word2, len1, len2, cash);

    if (print)  
        Matrix::print(cash, word1, word2);

    Matrix::release(cash, len2 + 1);

    return res;
}

int Algs::recursiveCash(wstring &word1, wstring &word2, int ind1, int ind2, int** cash) {

    if (cash[ind2][ind1] >= 0)
        return cash[ind2][ind1];

    if (min(ind1, ind2) == 0)
        return cash[ind2][ind1] = max(ind1, ind2);

    int dif = (word1[ind1 - 1] == word2[ind2 - 1]) ? 0 : 1;

    int res = min(recursiveCash(word1, word2, ind1 - 1, ind2 - 1, cash) + dif,
                  min(recursiveCash(word1, word2, ind1 - 1, ind2, cash) + 1, 
                      recursiveCash(word1, word2, ind1, ind2 - 1, cash) + 1));

    if (ind1 > 1 && ind2 > 1 && word1[ind1 - 1] == word2[ind2 - 2] && word1[ind1 - 2] == word2[ind2 - 1])
        res = min(res, recursiveCash(word1, word2, ind1 - 2, ind2 - 2, cash) + 1);

    cash[ind2][ind1] = res;

    return res;
}