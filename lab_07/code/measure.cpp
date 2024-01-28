#include "measure.h"

double getTotalTime(long long startT, long long endT) {
    return (double) (endT - startT);
}

long long getThreadCpuTimeNs() {
    
    struct timespec t;

    if (clock_gettime(CLOCK_THREAD_CPUTIME_ID, &t)) {
        perror("clock_gettime");
        return 0;
    }
    
    return (t.tv_sec * 1000000000LL + t.tv_nsec);
}

auto getCPUTime(func_ptr func, const string& text, const string& pattern) {
    
    long long startT, endT;

    startT = getThreadCpuTimeNs(); 
    func(text, pattern);
    endT = getThreadCpuTimeNs();

    return getTotalTime(startT, endT);
}

void genText(string& text, int len) {

    const string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz012345678";

    for (int i = 0; i < len; ++i) 
        text += characters[rand() % characters.length()];
}

void timeMeasure() {
    
    srand(time(NULL));

    int k = 100;
    int lenPattern = 10;

    vector Ns{256, 512, 1024, 2048, 4096};
    
    string text, pattern;

    for (int N : Ns) {

        pair<double, double> best(0, 0), 
                             worst_1(0, 0), 
                             worst_2(0, 0);

        genText(text, N);

        for (int i = 0; i < k; ++i) {

            for (int j = 0; j < lenPattern; ++j)
                pattern += text[j];

            best.first += getCPUTime(KMP, text, pattern);
            best.second += getCPUTime(KMP_optimized, text, pattern);
            
            pattern.clear();
        }

        for (int i = 0; i < k; ++i) {

            for (int j = 0; j < lenPattern; ++j)
                pattern += text[N - lenPattern + j];

            worst_1.first += getCPUTime(KMP, text, pattern);
            worst_1.second += getCPUTime(KMP_optimized, text, pattern);
            
            pattern.clear();
        }

        for (int i = 0; i < k; ++i) {

            for (int j = 0; j < lenPattern; ++j)
                pattern += text[j + j % 3];

            worst_2.first += getCPUTime(KMP, text, pattern);
            worst_2.second += getCPUTime(KMP_optimized, text, pattern);
            
            pattern.clear();
        }

        cout << "Длина строки:  " << N << " Длина подстроки: " << lenPattern << endl;
        cout << "Лучший случай: " << best.first / k << " " << best.second / k << endl;
        cout << "Худший случай 1: " << worst_1.first / k << " " << worst_1.second / k << endl;
        cout << "Худший случай 2: " << worst_2.first / k << " " << worst_2.second / k << endl;
        cout << endl;

        lenPattern *= 2;
        text.clear();
    }
}

void compMeasure() {

    ofstream kmpFile, kmpModFile;
    kmpFile.open("../graphs/time_kmp.csv", ios::trunc); 
    kmpModFile.open("../graphs/time_kmp_mod.csv", ios::trunc); 

    kmpFile << "str,under_str,best,worst1,worst2\n";
    kmpModFile << "str,under_str,best,worst1,worst2\n";
    
    srand(time(NULL));

    int k = 100;
    int lenPattern = 10;

    vector Ns{256, 512, 1024, 2048, 4096};
    pair<int, int> tmp;
    
    string text, pattern;

    for (int N : Ns) {

        genText(text, N);

        reset_comps();
        for (int i = 0; i < k; ++i) {

            for (int j = 0; j < lenPattern; ++j)
                pattern += text[j];

            KMP(text, pattern);
            KMP_optimized(text, pattern);
            
            pattern.clear();
        }
        tmp = get_comp_amt();

        cout << "Длина строки:  " << N << " Длина подстроки: " << lenPattern << endl;
        cout << "Лучший случай: " << tmp.first << " " << tmp.second << endl;

        kmpFile << N << "," << lenPattern << "," << tmp.first << "," << tmp.second << ",";
        kmpModFile << N << "," << lenPattern << "," << tmp.second << ",";

        reset_comps();
        for (int i = 0; i < k; ++i) {

            for (int j = 0; j < lenPattern; ++j)
                pattern += text[N - lenPattern + j];

            KMP(text, pattern);
            KMP_optimized(text, pattern);
            
            pattern.clear();
        }

        tmp = get_comp_amt();
        cout << "Худший случай 1: " << tmp.first << " " << tmp.second << endl;

        kmpFile <<  tmp.first << ",";
        kmpModFile <<  tmp.second << ",";

        reset_comps();
        for (int i = 0; i < k; ++i) {

            for (int j = 0; j < lenPattern; ++j)
                pattern += text[j + j % 3];

            KMP(text, pattern);
            KMP_optimized(text, pattern);
            
            pattern.clear();
        }

        tmp = get_comp_amt();
        cout << "Худший случай 2: " << tmp.first << " " << tmp.second << endl;

        kmpFile <<  tmp.first << "\n";
        kmpModFile <<  tmp.second << "\n";

        cout << endl;

        lenPattern *= 2;
        text.clear();
    }

    kmpFile.close();
    kmpModFile.close();
}

