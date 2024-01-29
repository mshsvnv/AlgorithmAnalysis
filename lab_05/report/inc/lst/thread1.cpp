void thread_1(size_t req_cnt, size_t n, size_t m, size_t cnt, queue<requestT *> &q1) {
    
    for (int i = 0; i < req_cnt; i++) {

        requestT *r = new requestT();

        clock_gettime(CLOCK_REALTIME, &r->p1_start);
        packData(n, m, cnt, r);

        mutex_q1.lock();
        clock_gettime(CLOCK_REALTIME, &r->p1_end);
        q1.push(r);
        mutex_q1.unlock();
    }
}