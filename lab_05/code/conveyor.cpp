#include "conveyor.h"

mutex mutex_q1;
mutex mutex_q2;

void packData(size_t n, size_t m, size_t cnt, requestT *r) {
    r->mtr_a = MatrixCSR(n, m, cnt);
    r->mtr_b = MatrixCSR(n, m, cnt);
}

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

int num = 1;
long long sum = 0;

void printPool(vector<requestT *> &pool, const string &filename) {
    
    vector<PoolResultT> pool_sort(pool.size() * 6);
    timespec min = pool[0]->p1_start;

    for (size_t i = 0; i < pool.size(); ++i) {
        if (min.tv_sec > pool[i]->p1_start.tv_sec || (min.tv_sec == pool[i]->p1_start.tv_sec && min.tv_nsec > pool[i]->p1_start.tv_nsec))
            min = pool[i]->p1_start;
    }

    long long min_nano = min.tv_sec * 1000000000 + min.tv_nsec;
    for (size_t i = 0; i < pool.size(); ++i) {

        long long nanosec = pool[i]->p1_start.tv_sec * 1000000000 + pool[i]->p1_start.tv_nsec;
        nanosec -= min_nano;
        char *buf = new char[50];
        snprintf(buf, 50, "Request %lu start creating: %lld ns", i, nanosec);
        // cout << buf << endl;
        pool_sort[i * 6].message = string(buf);
        pool_sort[i * 6].nanosec = nanosec;

        nanosec = pool[i]->p1_end.tv_sec * 1000000000 + pool[i]->p1_end.tv_nsec;
        nanosec -= min_nano;
        buf = new char[50];
        snprintf(buf, 50, "Request %lu end creating: %lld ns", i, nanosec);
        // cout << buf << endl;
        pool_sort[i * 6 + 1].message = string(buf);
        pool_sort[i * 6 + 1].nanosec = nanosec;

        nanosec = pool[i]->p2_start.tv_sec * 1000000000 + pool[i]->p2_start.tv_nsec;
        nanosec -= min_nano;
        buf = new char[50];
        snprintf(buf, 50, "Request %lu start sum: %lld ns", i, nanosec);
        // cout << buf << endl;
        pool_sort[i * 6 + 2].message = string(buf);
        pool_sort[i * 6 + 2].nanosec = nanosec;

        nanosec = pool[i]->p2_end.tv_sec * 1000000000 + pool[i]->p2_end.tv_nsec;
        nanosec -= min_nano;
        buf = new char[50];
        snprintf(buf, 50, "Request %lu end sum: %lld ns", i, nanosec);
        // cout << buf << endl;
        pool_sort[i * 6 + 3].message = string(buf);
        pool_sort[i * 6 + 3].nanosec = nanosec;

        nanosec = pool[i]->p3_start.tv_sec * 1000000000 + pool[i]->p3_start.tv_nsec;
        nanosec -= min_nano;
        buf = new char[50];
        snprintf(buf, 50, "Request %lu start unpack: %lld ns", i, nanosec);
        // cout << buf << endl;
        pool_sort[i * 6 + 4].message = string(buf);
        pool_sort[i * 6 + 4].nanosec = nanosec;

        nanosec = pool[i]->p3_end.tv_sec * 1000000000 + pool[i]->p3_end.tv_nsec;
        nanosec -= min_nano;
        buf = new char[50];
        snprintf(buf, 50, "Request %lu end unpack: %lld ns", i, nanosec);
        // cout << buf << endl;
        pool_sort[i * 6 + 5].message = string(buf);
        pool_sort[i * 6 + 5].nanosec = nanosec;
    }

    sort(pool_sort.begin(), pool_sort.end());
    ofstream fout;
    
    fout.open(filename, ios_base::app);
    sum += pool_sort[pool_sort.size() - 1].nanosec;
    
    if (num % LOOPS == 0) {
        fout << sum / LOOPS << endl;
        sum = 0;
    }

    ++num;
    fout.close();
}