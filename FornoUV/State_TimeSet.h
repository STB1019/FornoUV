#ifndef STATE_TIMESET_H
#define STATE_TIMESET_H

#include <Arduino.h>
#include "State.h"

#include "State_Idle.h"

#define BLINK_TIME_OFF  100
#define BLINK_TIME_ON   400

#define TIME_FORMAT_STRING "@h:@m"

class State_TimeSet : public State {
    public:
        State_TimeSet();
        ~State_TimeSet();
        void setup(State* prevState);
        State* execute(State* prevState);
        void printLCD(LiquidCrystal lcd, State* prevState);
        void printLCDOpt(LCDOptimizer* lcdOpt, State* prevState);
    protected:
    private:
        static const int cursorPos[][2];
        State_TimeSet(int sel);
        static bool lastBlinkingOn;
        static char rows[][17];
};

// SELECTION meaning:
// 0-3: time, 4 -> ok, 5 -> cancel




#endif
