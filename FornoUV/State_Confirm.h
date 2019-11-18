#ifndef STATE_CONFIRM_H
#define STATE_CONFIRM_H

#include <Arduino.h>
#include "State.h"

class State_Confirm : public State {
    public:
        State_Confirm();
        ~State_Confirm();
        State* execute(State* prevState);
    protected:
        void printLCD(LiquidCrystal lcd);
    private:

};






#endif
