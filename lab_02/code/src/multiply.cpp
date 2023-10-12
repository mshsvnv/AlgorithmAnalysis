#include "../inc/multiply.h"

MatrixT Standard::multiply(MatrixT& m1, MatrixT& m2) {

    MatrixT res{m1.m_rows, m2.m_columns};

    for (int i = 0; i < m1.m_rows; ++i) {

        for (int j = 0; j < m2.m_columns; ++j) {
            
            for (int k = 0; k < m1.m_columns; ++k) {

                res(i, j) += m1(i, k) * m2(k, j);
            }
        }
    }

    return res;
}

MatrixT Vinograd::multiply(MatrixT& m1, MatrixT& m2) {

    vector<int> ratioA;
    vector<int> ratioB;

    MatrixT res{m1.m_rows, m2.m_columns};

    for (int i = 0; i < m1.m_rows; ++i) {

        ratioA.emplace_back(0);

        for (int j = 0; j < m1.m_columns / 2; ++j) 
            ratioA[i] = ratioA[i] + m1(i, 2 * j) * m1(i, 2 * j + 1); 
        
    }

    for (int i = 0; i < m1.m_rows; ++i) {

        ratioB.emplace_back(0);

        for (int j = 0; j < m2.m_columns / 2; ++j) 
            ratioA[i] = ratioA[i] +  m2(2 * j, i) * m2(2 * j + 1, i);
        
    }

    for (int i = 0; i < m1.m_rows; ++i) {

        for (int j = 0; j < m2.m_columns; ++j) {
            
            res(i, j) = -ratioA[i] - ratioB[j];

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

    vector<int> ratioA;
    vector<int> ratioB;

    MatrixT res{m1.m_rows, m2.m_columns};

    for (int i = 0; i < m1.m_rows; ++i) {

        ratioA.emplace_back(0);

        for (int j = 0; j < stepHalf; ++j) 
            ratioA[i] += m1(i, j << 1) * m1(i, (j << 1) + 1); 
        
    }

    for (int i = 0; i < m2.m_rows; ++i) {

        ratioB.emplace_back(0);

        for (int j = 0; j < stepHalf; ++j) 
            ratioB[i] += m2(j << 1, i) * m2((j << 1) + 1, i);
        
    }

    for (int i = 0; i < m1.m_rows; ++i) {

        for (int j = 0; j < m2.m_columns; ++j) {
            
            res(i, j) = -ratioA[i] - ratioB[j];

            for (int k = 0; k < stepHalf; ++k) {

                res(i, j) += (m1(i, k << 1) + m2((k << 1) + 1, j)) * 
                             (m1(i, (k << 1) + 1) + m2(k << 1, j));
            
            }
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
