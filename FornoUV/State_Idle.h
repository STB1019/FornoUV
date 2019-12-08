#ifndef STATE_IDLE_H
#define STATE_IDLE_H

#include <Arduino.h>
#include "State.h"

#include "State_Confirm.h"
#include "State_TempSet.h"
#include "State_TimeSet.h"

class State_Idle : public State {
    public:
        State_Idle();
        ~State_Idle();
        void setup(State* prevState);
        State* execute(State* prevState);
        void printLCD(LiquidCrystal lcd, State* prevState);
        void printLCDOpt(LCDOptimizer* lcdOpt, State* prevState);
    protected:
    private:
        static const int cursorPos[][2];
        State_Idle(int sel);
        static char rows[][17];
};

// SELECTION meaning:
// 0 -> time, 1 -> temp, 2 -> start

#endif
