#include "../inc/algorithms.h"

// void printMtr(wstring &word1, wstring &word2, int** mtr) {

//     int m = word1.length();
//     int n = word2.length();
    
//     for (int i = 0; i <= n + 1; ++i) {

//         wcout << L"\t";
//         for (int j = 0; j <= m + 1; ++j) {

//             if (i == 0 && j > 1)
//                 wcout << word1[j - 2];
            
//             else if (j == 0 && i > 1)
//                 wcout << word2[i - 2];
            
//             else if (i > 0 && j > 0)
//                 wcout << mtr[i - 1][j - 1];

//             else
//                 wcout << L" ";

//             wcout << L" ";      
//         }
//         wcout << L"\n";      
//     }
// }

// int notRecursiveLev(wstring &word1, wstring &word2, bool print) {
    
//     int len1 = word1.length();
//     int len2 = word2.length();
    
//     int res = -1;

//     int** mtr = allocateMtr(len2 + 1, len1 + 1);

//     if (!mtr)
//         return res;

//     for (int i = 0; i <= len2; ++i) {

//         for (int j = 0; j <= len1; ++j) {

//             if (i == 0)
//                 mtr[i][j] = j;
//             else if (j == 0)
//                 mtr[i][j] = i;
//             else {
//                 int dif = (word1[j - 1] == word2[i - 1]) ? 0 : 1;

//                 mtr[i][j] = min(mtr[i - 1][j] + 1, 
//                             min(mtr[i][j - 1] + 1, mtr[i - 1][j - 1] + dif ) 
//                             );
//             }
//         }
//     }

//     if (print) printMtr(word1, word2, mtr);

//     res = mtr[len2][len1];
//     freeMtr(mtr, len2);

//     return res;
// }

int notRecursiveLev(wstring &word1, wstring &word2, int*** mtr) {
    
    int len1 = word1.length();
    int len2 = word2.length();
    
    int res = -1;

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

// int notRecursiveDamLev(wstring &word1, wstring &word2, bool print) {

//     int len1 = word1.length();
//     int len2 = word2.length();
    
//     int res = -1;

//     int** mtr = allocateMtr(len2 + 1, len1 + 1);

//     if (!mtr)
//         return res;

//     for (int i = 0; i <= len2; ++i) {

//         for (int j = 0; j <= len1; ++j) {

//             if (i == 0)
//                 mtr[i][j] = j;
//             else if (j == 0)
//                 mtr[i][j] = i;
//             else {
//                 int dif = (word1[j - 1] == word2[i - 1]) ? 0 : 1;

//                 mtr[i][j] = min(mtr[i - 1][j] + 1, 
//                             min(mtr[i][j - 1] + 1, mtr[i - 1][j - 1] + dif) 
//                             );

//                 if (i > 1 && j > 1 && word1[j - 2] == word2[i - 1] && word1[j - 1] == word2[i - 2]) 
//                     mtr[i][j] = min(mtr[i][j], mtr[i - 2][j - 2] + 1);
//             }
//         }
//     }

//     if (print) printMtr(word1, word2, mtr);

//     res = mtr[len2][len1];
//     freeMtr(mtr, len2);

//     return res;
// }

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
                               min((*mtr)[i][j - 1] + 1, (*mtr)[i - 1][j - 1] + dif) 
                               );

                if (i > 1 && j > 1 && word1[j - 2] == word2[i - 1] && word1[j - 1] == word2[i - 2]) 
                    (*mtr)[i][j] = min((*mtr)[i][j], (*mtr)[i - 2][j - 2] + 1);
            }
        }
    }

    return (*mtr)[len2][len1];
}

int recursive(wstring &word1, wstring &word2, int ind1, int ind2) {

    // int m = word1.length();
    // int n = word2.length();

    // if (ind1 == m && ind2 == n)
    //     return 0;

    // vector<int> subDist;

    // if (ind1 < m && ind2 < n) {
    //     int dif = (word1[ind1] == word2[ind2]) ? 0 : 1;

    //     subDist.emplace(subDist.begin(), recursive(word1, word2, ind1 + 1, ind2 + 1) + dif);
    // }
    
    // if (ind1 < m)
    //     subDist.emplace(subDist.begin(), recursive(word1, word2, ind1 + 1, ind2) + 1);

    // if (ind2 < n)
    //     subDist.emplace(subDist.begin(), recursive(word1, word2, ind1, ind2 + 1) + 1);

    // if (ind1 < m - 1 && ind2 < n - 1 && word1[ind1 + 1] == word2[ind2] && word1[ind1] == word2[ind2 + 1])
    //     subDist.emplace(subDist.begin(), recursive(word1, word2, ind1 + 2, ind2 + 2) + 1);

    // return *min_element(subDist.begin(), subDist.end());

    if (min(ind1, ind2) == 0)
        return max(ind1, ind2);

    vector<int> subDist;

    int dif = (word1[ind1 - 1] == word2[ind2 - 1]) ? 0 : 1;

    subDist.emplace(subDist.begin(), recursive(word1, word2, ind1 - 1, ind2 - 1) + dif);
    subDist.emplace(subDist.begin(), recursive(word1, word2, ind1 - 1, ind2) + 1);
    subDist.emplace(subDist.begin(), recursive(word1, word2, ind1, ind2 - 1) + 1);

    if (word1[ind1 - 1] == word2[ind2 - 2] && word1[ind1 - 2] == word2[ind2 - 1])
        subDist.emplace(subDist.begin(), recursive(word1, word2, ind1 - 2, ind2 - 2) + 1);

    return *min_element(subDist.begin(), subDist.end());
}

// int recursiveDamLev(wstring &word1, wstring &word2) {
//     return recursive(word1, word2, 0, 0);
// }

int recursiveCash(wstring &word1, wstring &word2, int ind1, int ind2, mapT& dict) {

    // int m = word1.length();
    // int n = word2.length();

    // if (ind1 == m && ind2 == n)
    //     return 0;

    // wstring key = to_wstring(ind1) + L":" + to_wstring(ind2);

    // if (dict[key])
    //     return dict[key];

    // vector<int> subDist;

    // if (ind1 < m && ind2 < n) {
    //     int dif = (word1[ind1] == word2[ind2]) ? 0 : 1;

    //     subDist.emplace(subDist.begin(), recursiveCash(word1, word2, ind1 + 1, ind2 + 1, dict) + dif);
    // }
    
    // if (ind1 < m)
    //     subDist.emplace(subDist.begin(), recursiveCash(word1, word2, ind1 + 1, ind2, dict) + 1);

    // if (ind2 < n)
    //     subDist.emplace(subDist.begin(), recursiveCash(word1, word2, ind1, ind2 + 1, dict) + 1);

    // if (ind1 < m - 1 && ind2 < n - 1 && word1[ind1 + 1] == word2[ind2] && word1[ind1] == word2[ind2 + 1])
    //     subDist.emplace(subDist.begin(), recursiveCash(word1, word2, ind1 + 2, ind2 + 2, dict) + 1);

    // dict[key] = *min_element(subDist.begin(), subDist.end());
    
    // return dict[key];

    if (min(ind1, ind2) == 0)
        return max(ind1, ind2);
    
    wstring key = to_wstring(ind1) + L":" + to_wstring(ind2);

    if (dict[key])
        return dict[key];

    vector<int> subDist;

    int dif = (word1[ind1 - 1] == word2[ind2 - 1]) ? 0 : 1;

    subDist.emplace(subDist.begin(), recursive(word1, word2, ind1 - 1, ind2 - 1) + dif);
    subDist.emplace(subDist.begin(), recursive(word1, word2, ind1 - 1, ind2) + 1);
    subDist.emplace(subDist.begin(), recursive(word1, word2, ind1, ind2 - 1) + 1);

    if (word1[ind1 - 1] == word2[ind2 - 2] && word1[ind1 - 2] == word2[ind2 - 1])
        subDist.emplace(subDist.begin(), recursive(word1, word2, ind1 - 2, ind2 - 2) + 1);

    dict[key] = *min_element(subDist.begin(), subDist.end());

    return dict[key];
}

// int recursiveDamLevCash(wstring& word1, wstring& word2, int ind1, int ind2) {
    
//     mapT dict;

//     return recursiveCash(word1, word2, 0, 0, dict);
// }