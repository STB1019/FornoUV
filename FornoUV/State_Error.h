#ifndef STATE_ERROR_H
#define STATE_ERROR_H

#include <Arduino.h>
#include "State.h"

class State_Error : public State {
    public:
        State_Error();
        ~State_Error();
        void setup(State* prevState);
        State* execute(State* prevState);
        void printLCD(LiquidCrystal lcd, State* prevState);
    protected:
    private:

};






#endif
