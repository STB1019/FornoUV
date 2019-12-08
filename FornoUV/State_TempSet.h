#ifndef STATE_TEMPSET_H
#define STATE_TEMPSET_H

#include <Arduino.h>
#include "State.h"

#include "State_Idle.h"

#include "utils.h"


class State_TempSet : public State {
    public:
        State_TempSet();
        ~State_TempSet();
        void setup(State* prevState);
        State* execute(State* prevState);
        void printLCD(LiquidCrystal lcd, State* prevState);
        void printLCDOpt(LCDOptimizer* lcdOpt, State* prevState);
    protected:
    private:
        static const int cursorPos[][2];
        State_TempSet(int sel);
};






#endif
