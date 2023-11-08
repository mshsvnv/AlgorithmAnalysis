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

auto getCPUTime(MatrixT& mtr1, MatrixT& mtr2, Multiply* mul) {
    
    long long startT, endT;

    startT = getThreadCpuTimeNs(); 
    MatrixT res = mul->multiply(mtr1, mtr2);
    endT = getThreadCpuTimeNs();

    return getTotalTime(startT, endT);
}

void printHead(int num) {

    if (num != 2) {
        cout << "+-------------------------------------------------------------------+\n";
        cout << "|       |                      Время(нс)                            |\n";
        cout << "| Длина |  Стандартное  |             Алгоритм Винограда            |\n";
        cout << "|(элем.)|               |  Неоптимизированный  |  Оптимизированный  |\n";
        cout << "+-------------------------------------------------------------------+\n";
    }
    else {
        cout << "+----------------------------------------------------------------------------------------+\n";
        cout << "|       |                                   Время(нс)                                    |\n";
        cout << "| Длина |  Стандартное  |             Алгоритм Винограда            | Алгоритм Штрассена |\n";
        cout << "|(элем.)|               |  Неоптимизированный  |  Оптимизированный  |                    |\n";
        cout << "+----------------------------------------------------------------------------------------+\n";
    }
}

void timeMeasure(int step, int iters, int maxAmount) {

    printHead(step);
    srand(time(NULL));

    int base = (step == 2) ? step : 10;

    vector<Multiply*> muls{new Standard, new Vinograd, new VinogradOpt};

    if (step == 2)
        muls.emplace_back(new Strassen);
    
    int len = muls.size();

    for (int i = step; i <= step + maxAmount;) {

        vector<double> times(len, 0);

        MatrixT mtr1(i, i);
        mtr1.randomFill();

        MatrixT mtr2(i, i);
        mtr2.randomFill();

        for (int j = 0; j < iters; ++j) {

            for (int k = 0; k < len; ++k)
                times[k] += getCPUTime(mtr1, mtr2, muls[k]);
        }

        for (int k = 0; k < len; ++k)
            times[k] /= (double)iters;

        cout << "| " << setw(5) << i << " │ "
        << fixed << setprecision(2) << setw(13) << times[0] << " │ "
        << fixed << setprecision(2) << setw(20) << times[1] << " │ "
        << fixed << setprecision(2) << setw(18) << times[2] << " │ ";

        if (len == 4)
            cout << fixed << setprecision(2) << setw(18) << times[3] << " │ "
            << "\n+----------------------------------------------------------------------------------------+\n";
        else
            cout << "\n+-------------------------------------------------------------------+\n";

        if (step == 2)
            i *= step;
        else
            i += base;   
    }
}