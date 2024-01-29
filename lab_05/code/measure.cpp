#include "measure.h"

double getTime(timespec start, timespec end) {
    return (end.tv_sec - start.tv_sec) * 1000000000 + end.tv_nsec - start.tv_nsec;
}

double parallelMeasure(size_t req_cnt, size_t size) {
    
    timespec start, end;

    clock_gettime(CLOCK_REALTIME, &start);
    vector<requestT *> pool(req_cnt);
    queue<requestT *> q1;
    queue<requestT *> q2;
    queue<requestT *> q3;

    thread t_1(thread_1, req_cnt, size, size, size / 2, ref(q1));
    thread t_2(thread_2, req_cnt, ref(q1), ref(q2));
    thread t_3(thread_3, req_cnt, ref(q2), ref(pool));

    t_1.join();
    t_2.join();
    t_3.join();
    clock_gettime(CLOCK_REALTIME, &end);
    printPool(pool, "m_parallel.txt");
    for (size_t i = 0; i < pool.size(); ++i)
        delete pool[i];

    double time = getTime(start, end);
    return time;
}

double linearMeasure(size_t req_cnt, size_t size) {

    timespec start, end;
    vector<requestT *> pool(req_cnt);

    clock_gettime(CLOCK_REALTIME, &start);

    for (int i = 0; i < req_cnt; i++) {
        requestT *r = new requestT();

        clock_gettime(CLOCK_REALTIME, &r->p1_start);
        packData(size, size, size / 2, r);
        clock_gettime(CLOCK_REALTIME, &r->p1_end);

        clock_gettime(CLOCK_REALTIME, &r->p2_start);
        r->mtr_c = r->mtr_a + r->mtr_b;
        clock_gettime(CLOCK_REALTIME, &r->p2_end);

        clock_gettime(CLOCK_REALTIME, &r->p3_start);
        r->result = r->mtr_c.decomprass();
        clock_gettime(CLOCK_REALTIME, &r->p3_end);

        pool[i] = r;
    }

    clock_gettime(CLOCK_REALTIME, &end);
    printPool(pool, "m_linear.txt");
    for (size_t i = 0; i < pool.size(); ++i)
        delete pool[i];

    double time = getTime(start, end);
    return time;
}

void timeMeasure1() {

    double tl = 0, tp = 0;

    printf("size,l,p\n");
    for (int i = 10; i <= MAX_REQUEST; i += 10) {
        for (int j = 0; j < LOOPS; j++) {
            tl += linearMeasure(i, MATRIX_SIZE);
            tp += parallelMeasure(i, MATRIX_SIZE);
        }
        if (tl > 0)
            tl /= (MATRIX_SIZE - 2) * 10000;
        if (tp > 0)
            tp /= (MATRIX_SIZE - 2) * 10000;
        printf("%d,%.2lf,%.2lf\n", i, tl, tp);
    }
}