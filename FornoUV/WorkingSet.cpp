#include "WorkingSet.h"

WorkingSet WorkingSet::_instance;

WorkingSet* WorkingSet::getInstance() {
    return &_instance;
}

WorkingSet::WorkingSet() {
    _timer = new Timer(0, 15, 0); // default: 15 minutes
    _targetTemp = 50; // default: 50°C
}

void WorkingSet::setInterruptNextState(ExecStateFunct interruptNextState) {
    this->_interruptNextState = interruptNextState;
}
ExecStateFunct WorkingSet::getInterruptNextState() {
    return this->_interruptNextState;
}

Timer* WorkingSet::getTimer() {
    return _timer;
}
void WorkingSet::createTmpTimer() {
    _tempTimer = new Timer(_timer);
}
Timer* WorkingSet::getTmpTimer() {
    return _tempTimer;
}
void WorkingSet::confirmTmpTimer() {
    delete _timer;
    _timer = _tempTimer;
    _tempTimer = NULL;
}
void WorkingSet::rejectTmpTimer() {
    delete _tempTimer;
}

float WorkingSet::getTargetTemp() {
    return (float) _targetTemp;
}
void WorkingSet::createTmpTargetTemp() {
    _tempTargetTemp = _targetTemp;
}
float WorkingSet::getTmpTargetTemp() {
    return _tempTargetTemp;
}
void WorkingSet::confirmTmpTargetTemp() {
    _targetTemp = _tempTargetTemp;
}
void WorkingSet::changeTmpTargetTemp(int amt) {
    _tempTargetTemp += amt;
}
