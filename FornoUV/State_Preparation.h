#ifndef STATE_PREPARATION_H
#define STATE_PREPARATION_H

#include <Arduino.h>
#include "State.h"

class State_Preparation : public State {
    public:
        State_Preparation();
        ~State_Preparation();
        void setup(State* prevState);
        State* execute(State* prevState);
        void printLCD(LiquidCrystal lcd, State* prevState);
        void printLCDOpt(LCDOptimizer lcdOpt, State* prevState);
    protected:
    private:
        State_Preparation(int sel);
};






#endif
