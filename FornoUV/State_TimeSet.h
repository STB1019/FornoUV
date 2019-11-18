#ifndef STATE_TIMESET_H
#define STATE_TIMESET_H

#include <Arduino.h>
#include "State.h"

#include "State_Idle.h"


class State_TimeSet : public State {
    public:
        State_TimeSet();
        ~State_TimeSet();
        State* execute(State* prevState);
        void printLCD(LiquidCrystal lcd, State* prevState);
    protected:
    private:
        State_TimeSet(int selected);
};

// SELECTION meaning:
// 0-3: time, 4 -> ok, 5 -> cancel




#endif
