#include "../inc/measure.h"

wstring generateWord(int len) {

    wstring word;
    
    wstring symbs = L"0123456789"
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "abcdefghijklmnopqrstuvwxyz"
                "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"
                "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";

    for (int i = 0; i < len; ++i) 
        word += symbs[rand() % (symbs.length() - 1)];

    return word;
}

static double getTotalTime(long long startT, long long endT) {
    return 1000000000LL * (double) (endT - startT) / CLOCKS_PER_SEC;
}

static long long getThreadCpuTimeNs() {
    
    struct timespec t;

    if (clock_gettime(CLOCK_THREAD_CPUTIME_ID, &t)) {
        perror("clock_gettime");
        return 0;
    }

    return t.tv_sec * 1000000000LL + t.tv_nsec;
}

auto getCPUTime(wstring& word1, wstring& word2, funcNotRecT fptr) {
    
    long long startT, endT;
    double totalT;

    int len1 = word1.length();
    int len2 = word2.length();

    // startT = getThreadCpuTimeNs();
    auto start = chrono::high_resolution_clock::now(); 
    int res = fptr(word1, word2, false);
    auto end = chrono::high_resolution_clock::now();
    // endT = getThreadCpuTimeNs();

    // return getTotalTime(startT, endT);
    auto total = chrono::duration_cast<chrono::nanoseconds>(end - start);
    // wcout << total << endl;

    return total;
}

auto getCPUTime(wstring& word1, wstring& word2, funcRecT fptr) {
    
    long long startT, endT;
    double totalT;

    int len1 = word1.length();
    int len2 = word2.length();

    // startT = getThreadCpuTimeNs();
    auto start = chrono::high_resolution_clock::now(); 
    int res = fptr(word1, word2, len1, len2);
    auto end = chrono::high_resolution_clock::now();
    // endT = getThreadCpuTimeNs();

    // return getTotalTime(startT, endT);
    auto total = chrono::duration_cast<chrono::nanoseconds>(end - start);

    return total;
}

auto getCPUTime(wstring& word1, wstring& word2, funcRecCashT fptr) {
    
    long long startT, endT;
    double totalT;
    
    mapT dict;
    int len1 = word1.length();
    int len2 = word2.length();

    // startT = getThreadCpuTimeNs();
    auto start = chrono::high_resolution_clock::now(); 
    int res = fptr(word1, word2, len1, len2, dict);
    auto end = chrono::high_resolution_clock::now();
    // endT = getThreadCpuTimeNs();

    // return getTotalTime(startT, endT);
    auto total = chrono::duration_cast<chrono::nanoseconds>(end - start);

    return total;
}

void printAlgs() {

    wcout << L"| Длина |  Левенштейн   |                Дамерау-Левенштейн             |\n";
    wcout << L"|(симв.)|  Итеративный  |  Итеративный  |             Рекурсивный       |\n";
    wcout << L"|       |               |               |    Без кэша    |     С кэшом  |\n";
}

void timeMeasure(int maxLen, int iters) {
    
    wcout << L"+-----------------------------------------------------------------------+\n";
    wcout << L"|       |                            Время(нс)                          |\n";
    printAlgs();
    wcout << L"+-----------------------------------------------------------------------+\n";
    
    wstring word1, word2;

    vector<chrono::nanoseconds> times;
    times.resize(4);

    for (int j = 0; j < times.size(); ++j)
        times[j] = (chrono::nanoseconds)0; 

    for (int i = 0; i <= maxLen;) {

        word1 = generateWord(i);
        word2 = generateWord(i);

        for (int j = 0; j < iters; ++j) {
            
            times[0] += getCPUTime(word1, word2, notRecursiveLev);
            times[1] += getCPUTime(word1, word2, notRecursiveDamLev);

            if (i < 11)
                times[2] += getCPUTime(word1, word2, recursive);
                times[3] += getCPUTime(word1, word2, recursiveCash);
        }

        for (int j = 0; j < times.size(); ++j)
            times[j] = times[j] / iters; 

        // for (int j = 0; j < times.size(); ++j)
        //     wcout << times[j] << " "; 
        // wcout << endl;

        std::wprintf(L"| %5d | %13d | %13d ", i, times[0],times[1]);

        if (i < 11)
            std::wprintf(L"| %13d | %13d |\n", times[2], times[3]);
        else
            std::wprintf(L"| %10s    | %10s    |\n", "-", "-");

        for (int j = 0; j < times.size(); ++j)
            times[j] = (chrono::nanoseconds)0; 

        if (i < 10)
            i++;
        else if (i < 100)
            i += 10;
        else    
            i += 100;
    }

    wcout << L"+-----------------------------------------------------------------------+\n";
    
}

int getNotRecursiveLev(int len) {
    return (len + 1) * (len + 1) * sizeof(int) +
           2 * sizeof(wchar_t) * len +
           2 * sizeof(int) +
           4 * sizeof(int) +
           sizeof(int**) + (len + 1) * sizeof(int*);
}

int getNotRecursiveDamLev(int len) {
    return getNotRecursiveLev(len);
}

int getRecursiveDam(int len) {
    return 2 * sizeof(int) + 
           2 * sizeof(wchar_t) * len 
           + sizeof(int*);
}

int getRecursiveDamCash(int len) {
    return getRecursiveDam(len) + sizeof(int) * len;
}

void memoryMeasure(int maxLen, int step) {

    wcout << L"+-----------------------------------------------------------------------+\n";
    wcout << L"|       |                    Размер (в байтах)                          |\n";
    printAlgs();
    wcout << L"+-----------------------------------------------------------------------+\n";
    
    
    for (int i = 0; i <= maxLen; i += step) {

        std::wprintf(L"| %5zu | %13zu | %13zu | %13zu | %13zu |\n",
                     i,
                     getNotRecursiveLev(i),
                     getNotRecursiveDamLev(i),
                     getRecursiveDam(i),
                     getRecursiveDamCash(i));
    }

    wcout << L"+-----------------------------------------------------------------------+\n";
    

}