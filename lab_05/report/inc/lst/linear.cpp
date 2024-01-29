void linear() {

    int req_cnt = getRequestNumber();
    int n = getMatrixN();
    int m = getMatrixM();
    int cnt = getMatrixNum();

    vector<requestT *> pool(req_cnt);

    for (int i = 0; i < req_cnt; i++) {

        requestT *r = new requestT();

        clock_gettime(CLOCK_REALTIME, &r->p1_start);
        packData(n, m, cnt, r);
        clock_gettime(CLOCK_REALTIME, &r->p1_end);

        clock_gettime(CLOCK_REALTIME, &r->p2_start);
        r->mtr_c = r->mtr_a + r->mtr_b;
        clock_gettime(CLOCK_REALTIME, &r->p2_end);

        clock_gettime(CLOCK_REALTIME, &r->p3_start);
        r->result = r->mtr_c.decomprass();
        clock_gettime(CLOCK_REALTIME, &r->p3_end);

        pool[i] = r;
    }
    
    printPool(pool, "linear.txt");

    for (size_t i = 0; i < pool.size(); ++i)
        delete pool[i];
}