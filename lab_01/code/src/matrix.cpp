#include "../inc/matrix.h"

int** Matrix::allocate(int rows, int columns, bool fill) {
    
    int** mtr = static_cast<int**>(malloc(rows * sizeof(int *)));

    if (mtr) {
        for (int i = 0; i < rows; ++i) {

            int* ptr = static_cast<int*>(malloc(columns * sizeof(int)));

            if (ptr)
                mtr[i] = ptr;
            else
                Matrix::release(mtr, rows);
        }
    }

    if (fill) {
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < columns; ++j)
                mtr[i][j] = 0;
    }

    return mtr;
}

void Matrix::release(int** mtr, int m) {

    if (*mtr) {

        for (auto i = 0; i < m; ++i) {

            if (mtr[i])
                free(mtr[i]);
        }

        free(mtr);
    }
}

void Matrix::print(int** mtr, wstring &word1, wstring &word2) {

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
                wcout << mtr[i - 1][j - 1];

            else
                wcout << L" ";

            wcout << L" ";      
        }
        wcout << L"\n";      
    }
}