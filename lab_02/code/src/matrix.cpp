#include "../inc/matrix.h"

ostream& operator>>(ostream& out, const MatrixT& mtr) {

    for (int i = 0; i < mtr.m_rows; ++i) {
        
        out << "\t";

        for (int j = 0; j < mtr.m_columns; ++j) {
            out << mtr.m_matrix[i][j] << " ";
        }

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

    cout << fileName;

    if (file.is_open() && file.good()) {

        cout << "here\n";
    

        while (getline(file, line)) {
            cout << line << endl;
        }
    }
}


// void inputSize(int& rows, int& columns) {
//     cout << "Строк: ";
//     cin >> rows;

//     cout << "Столбцов: ";
//     cin >> rows;
// }

// int fillMtr(int rows, int columns, matrixT& mtr) {

//     try {
//         rowT row;
//         row.resize(columns);
//         mtr.resize(rows, row);
//     }
//     catch(...) {
//         cerr << "Неверный размер";
//         return 1;
//     }

//     for (int i = 0; i < rows; ++i) {

//         for (int j = 0; j < columns; ++j) {

//             try {
//                 cin >> mtr[i][j];
//             }
//             catch(...) {
//                 cerr << "Неверное значение";
//                 return 1;
//             }
//         }
//     }
// }


// void printMtr(int rows, int columns, matrixT& mtr) {

//     for (int i = 0; i < rows; ++i) {

//         for (int j = 0; j < columns; ++j) {

//             cout << mtr[i][j] << " ";
//         }

//         cout << endl;
//     }
// }


