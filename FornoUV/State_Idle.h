#ifndef STATE_IDLE_H
#define STATE_IDLE_H

#include <Arduino.h>
#include "State.h"

#include "State_Confirm.h"
#include "State_TempSet.h"
#include "State_TimeSet.h"

class State_Idle : public State {
public:
    State_Idle();
    ~State_Idle();
    State* execute(State* prevState);
protected:
    void printLCD();
private:
    State_Idle(int sel);
};

// SELECTION meaning:
// 0 -> time, 1 -> temp, 2 -> start

#endif
