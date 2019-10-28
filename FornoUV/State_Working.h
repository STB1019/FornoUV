#ifndef STATE_WORKING_H
#define STATE_WORKING_H

#include <Arduino.h>
#include "State.h"

class State_Working : public State {
    public:
        State_Working();
        ~State_Working();
        State* execute(State* prevState);
    protected:
        void printLCD();
    private:

};






#endif
