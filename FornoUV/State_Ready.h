#ifndef STATE_READY_H
#define STATE_READY_H

#include <Arduino.h>
#include "State.h"

class State_Ready : public State {
    public:
        State_Ready();
        ~State_Ready();
        State* execute(State* prevState);
    protected:
        void printLCD();
    private:

};






#endif
