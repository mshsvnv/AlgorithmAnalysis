#include "../inc/measure.h"

wstring generateWord(int len) {

    wstring word;
    
    wstring symbs = L"0133456789"
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "abcdefghijklmnopqrstuvwxyz"
                "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"
                "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";

    for (int i = 0; i < len; ++i) 
        word += symbs[rand() % (symbs.length() - 1)];

    return word;
}

static double getTotalTime(long long startT, long long endT) {
    return (double) (endT - startT);
}

static long long getThreadCpuTimeNs() {
    
    struct timespec t;

    if (clock_gettime(CLOCK_THREAD_CPUTIME_ID, &t)) {
        perror("clock_gettime");
        return 0;
    }

    return t.tv_sec * 1000000000LL + t.tv_nsec;
}

auto getCPUTime(wstring& word1, wstring& word2, Algs::funcT fptr) {
    
    long long startT, endT;
    double totalT;

    int len1 = word1.length();
    int len2 = word2.length();

    startT = getThreadCpuTimeNs(); 
    int res = fptr(word1, word2, false);
    endT = getThreadCpuTimeNs();

    return getTotalTime(startT, endT);
}

auto getCPUTime(wstring& word1, wstring& word2, Algs::funcRecT fptr) {
    
    long long startT, endT;
    double totalT;

    int len1 = word1.length();
    int len2 = word2.length();

    startT = getThreadCpuTimeNs(); 
    int res = fptr(word1, word2, len1, len2);
    endT = getThreadCpuTimeNs();

    return getTotalTime(startT, endT);
}

void printHead() {

    wcout << L"+-----------------------------------------------------------------------+\n";
    wcout << L"|       |                            Время(нс)                          |\n";
    wcout << L"| Длина |  Левенштейн   |                Дамерау-Левенштейн             |\n";
    wcout << L"|(симв.)|  Итеративный  |  Итеративный  |             Рекурсивный       |\n";
    wcout << L"|       |               |               |    Без кэша    |     С кэшом  |\n";
    wcout << L"+-----------------------------------------------------------------------+\n";
}

void timeMeasure(int maxLen, int iters) {
    
    printHead();
    srand(time(NULL));

    wstring word1, word2;

    for (int i = 0; i <= maxLen;) {

        word1 = generateWord(i);
        word2 = generateWord(i);

        vector<double> times(4, 0);

        for (int j = 0; j < iters; ++j) {
            
            times[0] += getCPUTime(word1, word2, Algs::notRecursiveLev);
            times[1] += getCPUTime(word1, word2, Algs::notRecursiveDamLev);
            times[3] += getCPUTime(word1, word2, Algs::recursiveCash_Decor);

            if (i < 11)
                times[2] += getCPUTime(word1, word2, Algs::recursive);
                // times[3] += getCPUTime(word1, word2, Algs::recursiveCash_Decor);
        }

        for (int j = 0; j < times.size(); ++j)
            times[j] /= (double)iters; 

        std::wprintf(L"| %5d | %13.2g | %13.2g ", i, times[0],times[1]);

        if (i < 11)
            std::wprintf(L"| %13.2g | %13.2g |\n", times[2], times[3]);
        else
            // std::wprintf(L"| %10s    | %10s    |\n", "-", "-");
            std::wprintf(L"| %10s    | %13.2g |\n", "-", times[3]);
            
        if (i < 10)
            i++;
        else if (i < 100)
            i += 10;
        else    
            i += 100;
    }

    wcout << L"+-----------------------------------------------------------------------+\n";
}