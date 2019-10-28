#ifndef STATE_IDLE_H
#define STATE_IDLE_H

#include <Arduino.h>

class State_Idle : public State {
    public:
        State_Idle();
        ~State_Idle();
        State* execute(State* prevState);
    protected:
        void printLCD();
    private:

};






#endif
