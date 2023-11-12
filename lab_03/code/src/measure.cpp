#include "../inc/measure.h"

double getTotalTime(long long startT, long long endT) {
    return (double) (endT - startT);
}

long long getThreadCpuTimeNs() {
    
    struct timespec t;

    if (clock_gettime(CLOCK_THREAD_CPUTIME_ID, &t)) {
        perror("clock_gettime");
        return 0;
    }
    
    return (t.tv_sec * 1000000000LL + t.tv_nsec) / 1000;
}

auto getCPUTime(Sort* sort, ArrayT& arr) {
    
    long long startT, endT;

    startT = getThreadCpuTimeNs(); 
    sort->execute(arr);
    endT = getThreadCpuTimeNs();

    return getTotalTime(startT, endT);
}

void printHead(int num) {
    cout << "+-------------------------------------------------------+\n";
    cout << "|       |                    Время(нс)                  |\n";
    cout << "| Длина |     Radix     |      Comb     |     Shell     |\n";
    cout << "|(элем.)|               |               |               |\n";
    cout << "+-------------------------------------------------------+\n";
}

void timeMeasure(int step, int iters, int maxAmount, int type) {

    printHead(step);
    srand(time(NULL));

    vector<Sort*> sorts{new Radix, new Comb, new Shell};

    int len = sorts.size();

    for (int i = step; i <= step + maxAmount; i += step) {

        vector<double> times(len, 0);

        ArrayT arr(i, 0);

        switch (type)
        {
        case 1:
            arr.ascFill();
            break;
        case 2:
            arr.descFill();
            break;
        case 3:
            arr.randomFill();
            break;
        default:
            break;
        }
        
        for (int j = 0; j < iters; ++j) {

            for (int k = 0; k < len; ++k)
                times[k] += getCPUTime(sorts[k], arr);
        }

        for (int k = 0; k < len; ++k)
            times[k] /= (double)iters;

        cout << "| " << setw(5) << i << " │ "
        << fixed << setprecision(2) << setw(13) << times[0] << " │ "
        << fixed << setprecision(2) << setw(13) << times[1] << " │ "
        << fixed << setprecision(2) << setw(13) << times[2] << " │\n";

        cout << "+-------------------------------------------------------+\n";  
    }
}