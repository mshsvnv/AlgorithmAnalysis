void thread_2(int req_cnt, queue<requestT *> &q1, queue<requestT *> &q2) {
   
    for (int i = 0; i < req_cnt; i++) {

        while (q1.empty());
        
        mutex_q1.lock();
        requestT *r = q1.front();
        q1.pop();
        mutex_q1.unlock();

        clock_gettime(CLOCK_REALTIME, &r->p2_start);
        r->mtr_c = r->mtr_a + r->mtr_b;

        mutex_q2.lock();
        clock_gettime(CLOCK_REALTIME, &r->p2_end);
        q2.push(r);
        mutex_q2.unlock();
    }
}