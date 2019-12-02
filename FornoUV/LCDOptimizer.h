#ifndef LCDOPTIMIZER_H
#define LCDOPTIMIZER_H

#include <Arduino.h>
#include <LiquidCrystal.h>



class LCDOptimizer {
    public:
        LCDOptimizer(byte pin1, byte pin2, byte pin3, byte pin4, byte pin5, byte pin6, int numLine, int lineLength);
        ~LCDOptimizer();
        void clear();
        void printLine(int numLine, const char* str);

    private:
        static byte exclamation_point_2[];
        LiquidCrystal* lcd;
        int _numLine;
        int _lineLength;
        char** printed;

};


#endif
