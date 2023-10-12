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
    m_columns = idx / m_rows;
}

int& MatrixT::operator()(const int& i, const int& j) {
    return m_matrix[i][j];
}

