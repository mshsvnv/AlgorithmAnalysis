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