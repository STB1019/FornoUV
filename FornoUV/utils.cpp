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
    printMenuCursor(lcd, positions, ind, erase, false, 0, 0);
}
void printMenuCursor(LiquidCrystal* lcd, const int positions[][2], int ind, bool erase, bool blink,  int timeOn, int timeOff) {
    printMenuCursor(lcd, positions, ind, erase, blink, timeOn, timeOff, CURSOR);
}
void printMenuCursor(LiquidCrystal* lcd, const int positions[][2], int ind, bool erase, bool blink,  int timeOn, int timeOff, char cursor) {
    lcd->setCursor(positions[ind][0],positions[ind][1]);
    if (erase) {
        lcd->print(CURSOR_ERASE);
    }
    else if (blink) {
        if ((millis() / timeOff) % (1 + timeOn / timeOff) == 0) {
            lcd->print(CURSOR_ERASE);
        }
        else {
            lcd->print(cursor);
        }
    }
    else {
        lcd->print(cursor);
    }
}

void manageBlink(char* str, int index, int timeOn, int timeOff, char blinkChar) {
    if ((millis() / timeOff) % (1 + timeOn / timeOff) == 0) {
        str[index] = blinkChar;
    }
}