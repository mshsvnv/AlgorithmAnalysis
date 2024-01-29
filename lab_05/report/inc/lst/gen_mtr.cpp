MatrixCSR::MatrixCSR(size_t _n, size_t _m, size_t num_cnt) {

    int cnt = 0, prev = 0;
    n = _n;
    m = _m;

    for (size_t i = 0; i < n; i++) {

        srand(clock() % 1000000);
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