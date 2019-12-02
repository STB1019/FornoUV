#include "LCDOptimizer.h"

byte LCDOptimizer::exclamation_point_2[] = {
    B01110,
    B01110,
    B01110,
    B00100,
    B00000,
    B00100,
    B01110,
    B00100
};

LCDOptimizer::LCDOptimizer(byte pin1, byte pin2, byte pin3, byte pin4, byte pin5, byte pin6, int numLine, int lineLength) {
    this->lcd = new LiquidCrystal(pin1, pin2, pin3, pin4, pin5, pin6);
    this->_numLine = numLine;
    this->_lineLength = lineLength;

    printed = (char**)malloc(numLine * sizeof(char*));
    for(int i = 0; i < numLine; i++) {
        printed[i] = (char*)malloc(lineLength*sizeof(char));
        for(int j = 0; j < lineLength; j++)
            printed[i][j] = ' ';
    }

    lcd->begin(lineLength, numLine);
    lcd->createChar((byte) 0, exclamation_point_2);
}
LCDOptimizer::~LCDOptimizer() {
    for(int i = 0; i < this->_numLine; i++) {
        free(printed[i]);
    }
    free(printed);
    free(lcd);
}
void LCDOptimizer::clear() {
    this->lcd->clear();
}
/* Prints the line character by character only when the previous printed is different. */
void LCDOptimizer::printLine(int numLine, const char* str) {
    int lastPrinted = -1;
    char* line = printed[numLine];

    if (numLine < 0 || numLine >= this->_numLine)
        return;

    for(int i = 0; i < this->_lineLength && str[i] != '\0'; i++) {
        if (line[i] != str[i]) {
            line[i] = str[i];

            if (lastPrinted != i-1) {
                this->lcd->setCursor(i, numLine);
            }
            this->lcd->print(line[i]);
            lastPrinted = i;
        }
    }
}
