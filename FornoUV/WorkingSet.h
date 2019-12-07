#ifndef WORKING_SET_H
#define WORKING_SET_H

#include <Arduino.h>
#include "Timer.h"
#include "MachineState.h"

class WorkingSet {
    public:
        static WorkingSet* getInstance();

        void setInterruptNextState(ExecStateFunct interruptNextState);
        ExecStateFunct getInterruptNextState();

        /*TEMPERATURE*/
        float getTargetTemp();
        void createTmpTargetTemp();
        float getTmpTargetTemp();
        void confirmTmpTargetTemp();
        void changeTmpTargetTemp(int amt);

        /*TIME*/
        Timer* getTimer();
        void createTmpTimer();
        Timer* getTmpTimer();
        void confirmTmpTimer();
        void rejectTmpTimer();
    private:
        static WorkingSet _instance;
        WorkingSet();
        ExecStateFunct _interruptNextState;
        int _targetTemp;
        int _tmpTargetTemp;
        Timer _timer;
        Timer _tmpTimer;
};

#endif
