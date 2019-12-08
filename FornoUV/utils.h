#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>

void formatNum(char* out, int num, int len, char filler);
void formatNum(char* out, int num, int len, char filler = '0');

void formatNum(char* out, long num, int len, char filler);
void formatNum(char* out, long num, int len, char filler = '0');

void strCpy(char* dest, char* src, int startIndex);
void strFill(char* str, char filler, int from, int to);

#endif
