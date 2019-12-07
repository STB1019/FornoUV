#ifndef WORKING_SET_H
#define WORKING_SET_H

#include <Arduino.h>
#include "Timer.h";
#include "MachineState.h"

class WorkingSet {
    public:
        static WorkingSet* getInstance();

        void setInterruptNextState(ExecStateFunct interruptNextState);
        ExecStateFunct getInterruptNextState();


        Timer* getTimer();
        void createTmpTimer();
        Timer* getTmpTimer();
        void confirmTmpTimer();
        void rejectTmpTimer();

        float getTargetTemp();
        void createTmpTargetTemp();
        float getTmpTargetTemp();
        void confirmTmpTargetTemp();
        void changeTmpTargetTemp(int amt);
    private:
        static WorkingSet _instance;
        WorkingSet();
        ExecStateFunct _interruptNextState;
        Timer* _timer;
        Timer* _tempTimer;
        int _targetTemp;
        int _tempTargetTemp;
};

#endif
