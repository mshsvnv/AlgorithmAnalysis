void parallel() {
    
    int req_cnt = getRequestNumber();
    int n = getMatrixN();
    int m = getMatrixM();
    int cnt = getMatrixNum();

    vector<requestT *> pool(req_cnt);
    queue<requestT *> q1;
    queue<requestT *> q2;

    thread t_1(thread_1, req_cnt, n, m, cnt, ref(q1));
    thread t_2(thread_2, req_cnt, ref(q1), ref(q2));
    thread t_3(thread_3, req_cnt, ref(q2), ref(pool));

    t_1.join();
    t_2.join();
    t_3.join();

    printPool(pool, "parallel.txt");
    for (size_t i = 0; i < pool.size(); ++i)
        delete pool[i];
}