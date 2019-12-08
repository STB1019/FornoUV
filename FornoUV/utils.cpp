#include "utils.h";

void formatNum(char* out, int num, int len, char filler) {
    int i = len;
    out[i] = '\0';
    while (i > 0) {
        i--;
        int add = num % 10;
        num /= 10;

        out[i] = (num == 0 && add == 0) ? filler : ('0' + add);
    }
}
void formatNum(char* out, long num, int len, char filler) {
    int i = len;
    out[i] = '\0';
    while (i > 0) {
        i--;
        int add = (int) (num % 10);
        num /= 10;

        out[i] = (num == 0 && add == 0) ? filler : ('0' + add);
    }
}

void strCpy(char* dest, char* src, int startIndex) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i + startIndex] = src[i];
        i++;
    }
}

void strFill(char* str, char filler, int from, int to) {
    for (int i = from; i < to; i++) {
        str[i] = filler;
        i++;
    }
}
