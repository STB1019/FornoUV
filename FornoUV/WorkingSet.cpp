#include "WorkingSet.h"

WorkingSet WorkingSet::_instance;

WorkingSet* WorkingSet::getInstance() {
    return &_instance;
}

WorkingSet::WorkingSet() {
    _timer = Timer(0, 15, 0); // default: 15 minutes
    _tmpTimer = Timer(&_timer);
    _targetTemp = 50; // default: 50°C
    _tmpTargetTemp = _targetTemp;
}

void WorkingSet::setInterruptNextState(ExecStateFunct interruptNextState) {
    this->_interruptNextState = interruptNextState;
}
ExecStateFunct WorkingSet::getInterruptNextState() {
    return this->_interruptNextState;
}

/*TEMPERATURE*/
float WorkingSet::getTargetTemp() {
    return (float) _targetTemp;
}
void WorkingSet::createTmpTargetTemp() {
    _tmpTargetTemp = _targetTemp;
}
float WorkingSet::getTmpTargetTemp() {
    return _tmpTargetTemp;
}
void WorkingSet::confirmTmpTargetTemp() {
    _targetTemp = _tmpTargetTemp;
}
void WorkingSet::changeTmpTargetTemp(int amt) {
    _tmpTargetTemp += amt;
}


/*TIME*/
Timer* WorkingSet::getTimer() {
    return &_timer;
}
void WorkingSet::createTmpTimer() {
    _tmpTimer.clone(&_timer);
}
Timer* WorkingSet::getTmpTimer() {
    return &_tmpTimer;
}
void WorkingSet::confirmTmpTimer() {
    _timer.clone(&_tmpTimer);
}
void WorkingSet::rejectTmpTimer() {
    //DONOTHING
}

