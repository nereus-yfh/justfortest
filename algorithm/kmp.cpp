#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;

void get_next(char *pattern, int next[]) {
    int len = strlen(pattern);
    int pos = -1;
    next[0] = pos;
    for (int i = 1; i < len; i++) {
        while (pos > -1 && pattern[i] != pattern[pos+1]) pos = next[pos];
        if (pattern[i] == pattern[pos+1]) pos++;
        next[i] = pos;
    }
}

int kmp(char *txt, char *pattern) {
    int tlen = strlen(txt);
    int plen = strlen(pattern);
    if (plen == 0) {
        return 0;
    }
    int *next = new int[plen];
    get_next(pattern, next);
    int pos = -1;
    for (int i = 1; i < tlen; i++) {
        while(pos > -1 && pattern[pos+1] != txt[i]) pos = next[pos];
        if (pattern[pos+1] == txt[i]) pos++;
        if (plen - 1 == pos) {
            delete next; 
            return i - pos;
        }
    }
    delete next;
    return -1;
}

int main (int argc, char *argv[]) {
    if (argc < 3) {
        cerr << "./a.out txt pattern\n";
        return 1;
    }
    cout << kmp(argv[1], argv[2]);
}
