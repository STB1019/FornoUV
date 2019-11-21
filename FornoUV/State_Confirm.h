#ifndef STATE_CONFIRM_H
#define STATE_CONFIRM_H

#include <Arduino.h>
#include "State.h"

#include "State_Idle.h"
#include "State_Preparation.h"

#include "utils.h"

class State_Confirm : public State {
    public:
        State_Confirm();
        ~State_Confirm();
        void setup(State* prevState);
        State* execute(State* prevState);
        void printLCD(LiquidCrystal lcd, State* prevState);
    protected:
    private:
        static const int cursorPos[][2];

        State_Confirm(int sel);
};






#endif
