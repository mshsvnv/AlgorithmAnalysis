#include "matrix.h"

ostream& operator<<(ostream& stream, const vector<int>& vec) {
    
    for (int i = 0; i < vec.size(); i++)
        if (i == vec.size() - 1)
            stream << vec[i];
        else
            stream << vec[i] << ", ";

    return stream;
}

ostream& operator<<(ostream& stream, const MatrixCSR& mtr) {

    stream << "AN = [ ";
    stream << mtr.AN;
    stream << " ]" << std::endl;

    stream << "JA = [ ";
    stream << mtr.JA;
    stream << " ]" << std::endl;

    stream << "NR = [ ";
    stream << mtr.NR;
    stream << " ]" << std::endl;

    return stream;
}

MatrixCSR::MatrixCSR(size_t _n, size_t _m, size_t num_cnt) {

    int cnt = 0, prev = 0;
    n = _n;
    m = _m;

    for (size_t i = 0; i < n; i++) {

        int val = 0;

        for (size_t j = 0; cnt < num_cnt && j < m; j++) {
            
            if ((rand() % 15) - 5 > 0) {

                AN.push_back(rand() % 10 + 1);
                JA.push_back(j);
                
                cnt++;
                val++;
            }
        }

        if (i == 0)
            NR.push_back(0);
        else if (val == 0) {
            if (prev == 0)
                NR.push_back(NR[i - 1]);
            else
                NR.push_back(NR[i - 1] + prev);
        }
        else
            NR.push_back(NR[i - 1] + prev);
        prev = val;
    }

    NR.push_back(NR[n - 1] + (AN.size() - NR[n - 1]));
}

MatrixCSR MatrixCSR::operator+(const MatrixCSR &mtr) {
    
    MatrixCSR c; 

    c.n = n;
    c.m = m;

    int val = 0;

    for (int i = 0; i < NR.size() - 1; i++) {

        if (i == 0)
            c.NR.push_back(0);
        else
            c.NR.push_back(c.NR[i - 1] + val);

        val = 0;

        int ka = NR[i];
        int kb = mtr.NR[i];

        for (; ka < NR[i + 1] && kb < mtr.NR[i + 1];) {

            if (JA[ka] < mtr.JA[kb]) {
                c.JA.push_back(JA[ka]);
                c.AN.push_back(AN[ka++]);
            } else if (JA[ka] > JA[kb]) {
                c.JA.push_back(mtr.JA[kb]);
                c.AN.push_back(mtr.AN[kb++]);
            } else {
                auto tmp = AN[ka] + mtr.AN[kb];

                if (tmp) {
                    c.JA.push_back(JA[ka]);
                    c.AN.push_back(tmp);
                }
                ka++;
                kb++;
            }
            val++;
        }

        for (; ka < NR[i + 1]; ka++) {
            c.JA.push_back(JA[ka]);
            c.AN.push_back(AN[ka]);
            val++;
        }

        for (; kb < mtr.NR[i + 1]; kb++) {
            c.JA.push_back(mtr.JA[kb]);
            c.AN.push_back(mtr.AN[kb]);
            val++;
        }
    }

    c.NR.push_back(c.AN.size());
    return c;
}