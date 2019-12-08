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

void printMenuCursor(LiquidCrystal* lcd, const int positions[][2], int ind, bool erase) {
    lcd->setCursor(positions[ind][0],positions[ind][1]);
    if (erase)
        lcd->print(CURSOR_ERASE);
    else
        lcd->print(CURSOR);
}