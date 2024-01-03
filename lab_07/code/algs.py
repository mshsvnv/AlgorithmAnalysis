def makePiList(pattern):
    n = len(pattern)
    pi = [0] * n

    j = 0
    i = 1

    while (i < n):
        if pattern[j] == pattern[i]:
            pi[i] = j + 1
            j += 1
            i += 1
        else:
            if j == 0:
                pi[i] = 0
                i += 1
            else:
                j = pi[j - 1]
    return pi

def makeBadCharsList(pattern):
    n = len(pattern)
    badChars = {}

    for i in range(n):
        badChars[pattern[i]] = n - i - 1

    return badChars

def KMP(text, pattern):
    m = len(pattern)
    n = len(text)

    pi = makePiList(pattern)

    i = 0
    j = 0

    while (i < n):

        if text[i] == pattern[j]:
            i += 1
            j += 1

            if (j == m):
                return i - m
        else:
            if j == 0:
                i += 1
            else:
                j = pi[j - 1]
   
    return -1

def KMP_optimized(text, pattern):
    m = len(pattern)
    n = len(text)

    pi = makePiList(pattern)
    badChars = makeBadCharsList(pattern)
    shift = 0

    while shift <= n - m:
        j = m - 1

        while j >= 0 and pattern[j] == text[shift + j]:
            j -= 1

        if j < 0:
            return shift
        else:
            print(pi[j], badChars.get(text[shift + j]), m)
            print(shift)
            shift += max(pi[j], badChars.get(text[shift + j], m))
            print(shift)
    
    return -1

print(KMP_optimized("mamas", "as"))