#include "utils.h";

void formatNum(char* out, int num, int len) {
    int i = len;
    out[i] = '\0';
    while (i > 0) {
        i--;
        int add = num % 10;
        num /= 10;
        out[i] = '0' + add;
    }
}
