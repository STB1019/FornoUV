#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>
#include <LiquidCrystal.h>


#define CURSOR '>'
#define CURSOR_ERASE ' '

void formatNum(char* out, int num, int len);
void printMenuCursor(LiquidCrystal* lcd, const int positions[][2], int ind, bool erase);
void printMenuCursor(LiquidCrystal* lcd, const int positions[][2], int ind, bool erase, bool blink, int timeOn,  int timeOff);
void printMenuCursor(LiquidCrystal* lcd, const int positions[][2], int ind, bool erase, bool blink, int timeOn,  int timeOff, char cursor);
void manageBlink(char* str, int index, int timeOn, int timeOff, char blinkChar);

#endif
