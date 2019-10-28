#ifndef STATE_TIMESET_H
#define STATE_TIMESET_H

#include <Arduino.h>
#include "State.h";

class State_TimeSet : public State {
    public:
        State_TimeSet();
        ~State_TimeSet();
        State* execute(State* prevState);
    protected:
        void printLCD();
    private:

};






#endif
