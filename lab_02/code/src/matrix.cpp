#include "../inc/matrix.h"

ostream& operator<<(ostream& out, const MatrixT& mtr) {

    for (int i = 0; i < mtr.m_rows; ++i) {
        
        out << "\t";

        for (int j = 0; j < mtr.m_columns; ++j)
            out << mtr.m_matrix[i][j] << " ";

        out << endl;
    }

    return out;
}

MatrixT::MatrixT(int rows, int columns) : m_rows(rows), m_columns(columns) {

    m_matrix.resize(m_rows);

    for (int i = 0; i < m_rows; ++i)
        m_matrix[i].resize(columns);
}

MatrixT::MatrixT(const char* fileName) {
    
    ifstream file(fileName);
    string line;

    int rows = 0;

    int curElem = 0, idx = 0;

    if (file.is_open() && file.good()) {
    
        while (getline(file, line)) {
            
            stringstream curRow(line);

            vector<int> tmp;

            while(1) {
                curRow >> curElem;

                if (!curRow)
                    break;
                
                idx++;
                tmp.emplace_back(curElem);
            }
            rows++;

            m_matrix.emplace_back(tmp);
        }
    }

    m_rows = rows;

    if (m_rows)
        m_columns = idx / m_rows;
}

MatrixT MatrixT::copy(int begRow, int endRow, int begCol, int endCol) {
    
    MatrixT res{endRow - begRow, endCol - begCol};

    for (int i = begRow; i < endRow; ++i) {

        for (int j = begCol; j < endCol; ++j)
            res(i - begRow, j - begCol) = (*this)(i, j);
    }

    return res;
}

int& MatrixT::operator()(const int& i, const int& j) {
    return m_matrix[i][j];
}

int MatrixT::operator()(const int& i, const int& j) const {
    return m_matrix[i][j];
}

void MatrixT::randomFill() {

    for (int i = 0; i < m_rows; ++i) {

        for (int j = 0; j < m_columns; ++j) {
            (*this)(i, j) = rand() % 1000 - 1000;
        }
    }
}

MatrixT MatrixT::operator+(const MatrixT& other) {

    MatrixT res{m_rows, m_columns};

    for (int i = 0; i < m_rows; ++i) {

        for (int j = 0; j < m_columns; ++j)
            res(i, j) = (*this)(i, j) + other(i, j);
    }

    return res;
}

MatrixT MatrixT::operator-(const MatrixT& other) {

    MatrixT res{m_rows, m_columns};

    for (int i = 0; i < m_rows; ++i) {

        for (int j = 0; j < m_columns; ++j)
            res(i, j) = (*this)(i, j) - other(i, j);
    }

    return res;
}

void MatrixT::merge(const MatrixT& c11, const MatrixT& c12, const MatrixT& c21, const MatrixT& c22) {

    int n = m_rows / 2;

    for (int i = 0; i < n; ++i) {

        for (int j = 0; j < n; ++j) {
            (*this)(i, j) = c11(i, j);
            (*this)(i, n + j) = c12(i, j);
            (*this)(n + i, j) = c21(i, j);
            (*this)(n + i, n + j) = c22(i, j);
        }
    }
}

