#include "../inc/multiply.h"

MatrixT Standard::multiply(MatrixT& m1, MatrixT& m2) {

    MatrixT res{m1.m_rows, m2.m_columns};

    for (int i = 0; i < m1.m_rows; ++i) {

        for (int j = 0; j < m2.m_columns; ++j) {
            
            for (int k = 0; k < m1.m_columns; ++k) {

                res(i, j) = res(i, j) + m1(i, k) * m2(k, j);
            }
        }
    }

    return res;
}

MatrixT Vinograd::multiply(MatrixT& m1, MatrixT& m2) {

    vector<int> mulH;
    vector<int> mulV;

    MatrixT res{m1.m_rows, m2.m_columns};

    for (int i = 0; i < m1.m_rows; ++i) {

        mulH.emplace_back(0);

        for (int j = 0; j < m1.m_columns / 2; ++j) 
            mulH[i] = mulH[i] + m1(i, 2 * j) * m1(i, 2 * j + 1); 
        
    }

    for (int i = 0; i < m1.m_rows; ++i) {

        mulV.emplace_back(0);

        for (int j = 0; j < m2.m_columns / 2; ++j) 
            mulV[i] = mulV[i] +  m2(2 * j, i) * m2(2 * j + 1, i);
        
    }

    for (int i = 0; i < m1.m_rows; ++i) {

        for (int j = 0; j < m2.m_columns; ++j) {
            
            res(i, j) = -mulH[i] - mulV[j];

            for (int k = 0; k < m1.m_columns / 2; ++k) {

                res(i, j) = res(i, j) + (m1(i, 2 * k) + m2(2 * k + 1, j)) * 
                                        (m1(i, 2 * k + 1) + m2(2 * k, j));
            
            }
        }
    }

    if (m1.m_rows % 2) {

        for (int i = 0; i < m1.m_rows; ++i) {

            for (int j = 0; j < m2.m_columns; ++j) {       
                            
                res(i, j) = res(i, j) + m1(i, m1.m_columns - 1) * 
                                        m2(m2.m_rows - 1, j);

            }
        }
    }

    return res;    
}

MatrixT VinogradOpt::multiply(MatrixT& m1, MatrixT& m2) {

    int stepHalf = m1.m_columns / 2;

    vector<int> mulH;
    vector<int> mulV;

    MatrixT res{m1.m_rows, m2.m_columns};

    for (int i = 0; i < m1.m_rows; ++i) {

        mulH.emplace_back(0);

        for (int j = 0; j < stepHalf; ++j) 
            mulH[i] += m1(i, j << 1) * m1(i, (j << 1) + 1); 
        
    }

    for (int i = 0; i < m2.m_rows; ++i) {

        mulV.emplace_back(0);

        for (int j = 0; j < stepHalf; ++j) 
            mulV[i] += m2(j << 1, i) * m2((j << 1) + 1, i);
        
    }

    for (int i = 0; i < m1.m_rows; ++i) {

        for (int j = 0; j < m2.m_columns; ++j) {
            
            int buf = -mulH[i] - mulV[j];

            for (int k = 0; k < stepHalf; ++k) {
                
                int curK = k << 1;

                buf += (m1(i, curK) + m2(curK + 1, j)) * 
                             (m1(i, curK + 1) + m2(curK, j));
            
            }

            res(i, j) = buf;
        }
    }

    if (m1.m_rows % 2) {
        
        for (int i = 0; i < m1.m_rows; ++i) {

            for (int j = 0; j < m2.m_columns; ++j) {       
                            
                res(i, j) += m1(i, m1.m_columns - 1) * 
                             m2(m2.m_rows - 1, j);

            }
        }
    }

    return res;
}
