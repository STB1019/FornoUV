#ifndef STATE_H
#define STATE_H

#include "Actuator.h"
#include "WorkingSet.h"

#define STATE_ID_IDLE  0
#define STATE_ID_TIMESET  1
#define STATE_ID_TEMPSET  2
#define STATE_ID_CONFIRM  3
#define STATE_ID_PREPARATION  4
#define STATE_ID_READY  5
#define STATE_ID_WORKING  6
#define STATE_ID_FINISH  7
#define STATE_ID_ERROR  8

class State {
    public:
        virtual State* execute(State* prevState) = 0;
        int getStateId();
    protected:
        virtual void printLCD() = 0;
        void setStateId(int id);
    private:
        int _id;
};






#endif
