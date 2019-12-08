#ifndef STATE_WORKING_H
#define STATE_WORKING_H

#include <Arduino.h>
#include "State.h"

class State_Working : public State {
    public:
        State_Working();
        ~State_Working();
        void setup(State* prevState);
        State* execute(State* prevState);
        void printLCD(LiquidCrystal lcd, State* prevState);
        void printLCDOpt(LCDOptimizer* lcdOpt, State* prevState);
    protected:
    private:

};






#endif
