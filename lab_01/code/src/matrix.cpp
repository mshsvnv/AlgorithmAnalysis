#include "../inc/matrix.h"

void allocateMtr(int*** mtr, int m, int n) {
    
    if (!m) return;

    *mtr = static_cast<int**>(malloc(m * sizeof(int *)));

    if (mtr) {
        for (int i = 0; i < m; ++i) {

            int* ptr = static_cast<int*>(malloc(n * sizeof(int)));

            if (ptr)
                (*mtr)[i] = ptr;
            else
                freeMtr(mtr, m);
        }
    }
}

void freeMtr(int*** mtr, int m) {

    if (*mtr) {

        for (auto i = 0; i < m; ++i) {

            if ((*mtr)[i])
                free((*mtr)[i]);
        }

        free(*mtr);
    }
}

void printMtr(wstring &word1, wstring &word2, int*** mtr) {

    int m = word1.length();
    int n = word2.length();

    wcout << L"\n"; 
    
    for (int i = 0; i <= n + 1; ++i) {

        wcout << L"\t";
        for (int j = 0; j <= m + 1; ++j) {

            wcout << L" ";

            if (i == 0 && j > 1)
                wcout << word1[j - 2];
            
            else if (j == 0 && i > 1)
                wcout << word2[i - 2];
            
            else if (i > 0 && j > 0)
                wcout << (*mtr)[i - 1][j - 1];

            else
                wcout << L" ";

            wcout << L" ";      
        }
        wcout << L"\n";      
    }
}