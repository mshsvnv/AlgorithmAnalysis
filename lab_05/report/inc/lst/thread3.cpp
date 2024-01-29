void thread_3(int req_cnt, queue<requestT *> &q2, vector<requestT *> &pool) {
    
    for (int i = 0; i < req_cnt; i++) {

        while (q2.empty());

        mutex_q2.lock();
        requestT *r = q2.front();
        q2.pop();
        mutex_q2.unlock();

        clock_gettime(CLOCK_REALTIME, &r->p3_start);
        r->result = r->mtr_c.decomprass();
        clock_gettime(CLOCK_REALTIME, &r->p3_end);
        pool[i] = r;
    }
}