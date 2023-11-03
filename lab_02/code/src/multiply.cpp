#include "../inc/multiply.h"

bool isDegree(int num) {
    if (num % 2)
        return false;
    else {
        int x = 2;

        while (x < num)
            x <<= 1;

        return x == num;
    }
}

MatrixT Standard::multiply(MatrixT& m1, MatrixT& m2) {

    int rows = m1.getRows(), 
        columns = m2.getColumns(),
        tmp = m1.getColumns();

    MatrixT res{rows, columns};

    for (int i = 0; i < rows; ++i) {

        for (int j = 0; j < columns; ++j) {
            
            for (int k = 0; k < columns; ++k) {

                res(i, j) = res(i, j) + m1(i, k) * m2(k, j);
            }
        }
    }

    return res;
}

MatrixT Vinograd::multiply(MatrixT& m1, MatrixT& m2) {

    int rows = m1.getRows();

    MatrixT res{rows, rows};

    vector<int> mulH(rows, 0);
    vector<int> mulV(rows, 0);

    for (int i = 0; i < rows; ++i) {

        for (int j = 0; j < rows / 2; ++j) 
            mulH[i] = mulH[i] + m1(i, 2 * j) * m1(i, 2 * j + 1); 
        
    }

    for (int i = 0; i < rows; ++i) {

        for (int j = 0; j < rows / 2; ++j) 
            mulV[i] = mulV[i] +  m2(2 * j, i) * m2(2 * j + 1, i);
        
    }

    for (int i = 0; i < rows; ++i) {

        for (int j = 0; j < rows; ++j) {
            
            res(i, j) = -mulH[i] - mulV[j];

            for (int k = 0; k < rows / 2; ++k) {

                res(i, j) = res(i, j) + (m1(i, 2 * k) + m2(2 * k + 1, j)) * 
                                        (m1(i, 2 * k + 1) + m2(2 * k, j));
            
            }
        }
    }

    if (rows % 2) {

        for (int i = 0; i < rows; ++i) {

            for (int j = 0; j < rows; ++j) {       
                            
                res(i, j) = res(i, j) + m1(i, rows - 1) * 
                                        m2(rows - 1, j);

            }
        }
    }

    return res;    
}

MatrixT VinogradOpt::multiply(MatrixT& m1, MatrixT& m2) {

    int rows = m1.getRows();

    MatrixT res{rows, rows};

    vector<int> mulH(rows, 0);
    vector<int> mulV(rows, 0);

    int stepHalf = rows / 2;

    for (int i = 0; i < rows; ++i) {

        for (int j = 0; j < stepHalf; ++j) 
            mulH[i] += m1(i, j << 1) * m1(i, (j << 1) + 1); 

        cout << "i: " << mulH[i] << endl;
    }

    cout << endl;

    for (int i = 0; i < rows; ++i) {

        cout << mulV[i] << endl ;

        for (int j = 0; j < stepHalf; ++j) 
            mulV[i] += m2(j << 1, i) * m2((j << 1) + 1, i);

        cout << mulV[i] << " ";
    }

    cout << endl;

    for (int i = 0; i < rows; ++i) {

        for (int j = 0; j < rows; ++j) {
            
            int buf = -mulH[i] - mulV[j];

            for (int k = 0; k < stepHalf; ++k) {
                
                int curK = k << 1;

                buf += (m1(i, curK) + m2(curK + 1, j)) * (m1(i, curK + 1) + m2(curK, j));
            
            }

            res(i, j) = buf;
        }
    }

    if (rows % 2) {
        
        for (int i = 0; i < rows; ++i) {

            for (int j = 0; j < rows; ++j) {       
                            
                res(i, j) += m1(i, rows - 1) * 
                             m2(rows - 1, j);

            }
        }
    }

    return res;
}

MatrixT Strassen::multiply(MatrixT& m1, MatrixT& m2) {
    
    int rows = m1.getRows();

    if (rows <= 2)
        return bruteForce(m1, m2);

    int n = rows / 2;

    auto a = m1.copy(0, n, 0, n);
    auto b = m1.copy(0, n, n, rows);
    auto c = m1.copy(n, rows, 0, n);
    auto d = m1.copy(n, rows, n, rows);

    auto e = m2.copy(0, n, 0, n);
    auto f = m2.copy(0, n, n, rows);
    auto g = m2.copy(n, rows, 0, n);
    auto h = m2.copy(n, rows, n, rows);

    auto ad = a + d;
    auto eh = e + h;
    auto p1 = multiply(ad, eh);

    auto ge = g - e;
    auto p2 = multiply(d, ge);

    auto ab = a + b;
    auto p3 = multiply(ab, h);

    auto bd = b - d;
    auto gh = g + h;
    auto p4 = multiply(bd, gh);

    auto fh = f - h;
    auto p5 = multiply(a, fh);

    auto cd = c + d;
    auto p6 = multiply(cd, e);

    auto ac = a - c;
    auto ef = e + f;
    auto p7 = multiply(ac, ef);

    auto c11 = p1 + p2 - p3 + p4;
    auto c12 = p5 + p3;
    auto c21 = p6 + p2;
    auto c22 = p5 + p1 - p6 - p7;

    MatrixT res{rows, rows};

    res.merge(c11, c12, c21, c22);

    return res;
}

MatrixT Strassen::bruteForce(MatrixT& m1, MatrixT& m2) {

    int rows = m1.getRows();

    MatrixT res{rows, rows};

    for (int i = 0; i < rows; ++i) {

        for (int j = 0; j < rows; ++j) {
            
            for (int k = 0; k < rows; ++k) {

                res(i, j) = res(i, j) + m1(i, k) * m2(k, j);
            }
        }
    }

    return res;
}