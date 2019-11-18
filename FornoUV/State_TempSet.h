#ifndef STATE_TEMPSET_H
#define STATE_TEMPSET_H

#include <Arduino.h>
#include "State.h"

#include "State_Idle.h"


class State_TempSet : public State {
    public:
        State_TempSet();
        ~State_TempSet();
        State* execute(State* prevState);
    protected:
        void printLCD();
    private:
        State_TempSet(int selected);
};






#endif
