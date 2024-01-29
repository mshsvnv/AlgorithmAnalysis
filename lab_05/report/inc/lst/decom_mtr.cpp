MatrixT MatrixCSR::decomprass() {

    MatrixT mtr;
    
    mtr.m = m;
    mtr.n = n;

    for (int i = 0; i < n; i++ )
    {
        mtr.arr.emplace_back();
        for (int j = 0; j < m; j++ )
            mtr.arr.back().push_back(0);
    }

    int mtr_i = 0;
    for (int i = 0; i < n; i++) {
        
        for (int j = NR[i]; j < NR[i + 1]; j++)
            mtr.arr[mtr_i][JA[j]] = AN[j];
        mtr_i++;
    }

    return mtr;
}