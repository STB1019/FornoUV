#ifndef STATE_READY_H
#define STATE_READY_H

#include <Arduino.h>
#include "State.h"

class State_Ready : public State {
    public:
        State_Ready();
        ~State_Ready();
        void setup(State* prevState);
        State* execute(State* prevState);
        void printLCD(LiquidCrystal lcd, State* prevState);
        void printLCDOpt(LCDOptimizer* lcdOpt, State* prevState);
    protected:
    private:

};






#endif
