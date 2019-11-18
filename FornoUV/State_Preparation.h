#ifndef STATE_PREPARATION_H
#define STATE_PREPARATION_H

#include <Arduino.h>
#include "State.h"

class State_Preparation : public State {
    public:
        State_Preparation();
        ~State_Preparation();
        State* execute(State* prevState);
    protected:
        void printLCD(LiquidCrystal lcd);
    private:

};






#endif
