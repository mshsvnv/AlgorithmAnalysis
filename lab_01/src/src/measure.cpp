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

static long long getThreadCpuTimeNs() {
    
    struct timespec t;

    if (clock_gettime(CLOCK_THREAD_CPUTIME_ID, &t)) {
        perror("clock_gettime");
        return 0;
    }

    return t.tv_sec * 1000000000LL + t.tv_nsec;
}

double getCPUTime(wstring& word1, wstring& word2, funcNotRecT fptr) {
    
    long long startT, endT;
    double totalT;

    int** mtr;

    int len1 = word1.length();
    int len2 = word2.length();

    allocateMtr(&mtr, len2 + 1, len1 + 1);

    startT = getThreadCpuTimeNs();
    int res = fptr(word1, word2, &mtr);
    endT = getThreadCpuTimeNs();

    freeMtr(&mtr, len2 + 1);

    totalT = (double) (endT - startT) / CLOCKS_PER_SEC;
    return totalT;
}

double getCPUTime(wstring& word1, wstring& word2, funcRecT fptr) {
    
    long long startT, endT;
    double totalT;

    int len1 = word1.length();
    int len2 = word2.length();

    startT = getThreadCpuTimeNs();
    int res = fptr(word1, word2, len1, len2);
    endT = getThreadCpuTimeNs();

    // std::cout << endT << std::endl;
    totalT = (double) (endT - startT) / CLOCKS_PER_SEC;
    return totalT;
}

double getCPUTime(wstring& word1, wstring& word2, funcRecCashT fptr) {
    
    long long startT, endT;
    double totalT;
    
    mapT dict;
    int len1 = word1.length();
    int len2 = word2.length();

    startT = getThreadCpuTimeNs();
    int res = fptr(word1, word2, len1, len2, dict);
    endT = getThreadCpuTimeNs();

    totalT = (double) (endT - startT) / CLOCKS_PER_SEC;
    return totalT;
}

void printAlgs() {

    wcout << L"| Длина |  Левенштейн   |                Дамерау-Левенштейн                |\n";
    wcout << L"|(симв.)|  Итеративный  |  Итеративный  |             Рекурсивный          |\n";
    wcout << L"|       |               |               |    Без кэша    |     С кэшом     |\n";
}

void timeMeasure(int maxLen, int iters) {
    
    wcout << L"+--------------------------------------------------------------+\n";
    wcout << L"|       |                      Время(нс)                       |\n";
    printAlgs();
    wcout << L"+--------------------------------------------------------------+\n";
    
    wstring word1, word2;

    vector<double> times{0, 0, 0, 0};

    for (int i = 0; i < maxLen;) {

        word1 = generateWord(i);
        word2 = generateWord(i);

        for (int j = 0; j < iters; ++j) {
            
            times[0] += getCPUTime(word1, word2, notRecursiveLev);
            times[1] += getCPUTime(word1, word2, notRecursiveDamLev);

            if (i < 10)
                times[2] += getCPUTime(word1, word2, recursive);
                times[3] += getCPUTime(word1, word2, recursiveCash);
        }

        for (int j = 0; j < times.size(); ++j)
            times[j] = times[j] / iters; 

        std::wprintf(L"| %5d | %13.8g | %13.5g ", i, times[0],times[1]);

        if (i < 10)
            std::wprintf(L"| %13.5g | %13.5g |\n", times[2], times[3]);
        else
            std::wprintf(L"| %10s    | %10s    |\n", "-", "-");

        for (int j = 0; j < times.size(); ++j)
            times[j] = 0;

        if (i < 10)
            i++;
        else if (i < 100)
            i += 10;
        else    
            i += 100;
    }

    wcout << L"+--------------------------------------------------------------+\n";
    
}

int getNotRecursiveLev(int len) {
    return (len + 1) * (len + 1) * sizeof(int) +
           2 * sizeof(std::wstring) +
           2 * sizeof(int) +
           2 * sizeof(int) +
           sizeof(int **) + (len + 1) * sizeof(int *);
}

int getNotRecursiveDamLev(int len) {
    return 0;
}

int getRecursiveDam(int len) {
    return 0;
}

int getRecursiveDamCash(int len) {
    return 0;
}

void memoryMeasure(int maxLen, int step) {

    wcout << L"+--------------------------------------------------------------+\n";
    wcout << L"|       |                   Размер(байтах)                     |\n";
    printAlgs();
    wcout << L"+--------------------------------------------------------------+\n";
    
    
    for (int i = 0; i < maxLen; i += step) {

        std::wprintf(L"| %5zu | %13zu | %13zu | %8zu | %9zu |\n",
                     i,
                     getNotRecursiveLev(i),
                     getNotRecursiveDamLev(i),
                     getRecursiveDam(i),
                     getRecursiveDamCash(i));
    }

}