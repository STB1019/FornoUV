#include "WorkingSet.h"

WorkingSet* WorkingSet::_instance = NULL;

WorkingSet* WorkingSet::getInstance() {
    if (_instance == NULL) {
        _instance = new WorkingSet();
    }
    return _instance;
}

WorkingSet::WorkingSet() {
    _timer = new Timer(0, 15, 0); // default: 15 minutes
}

/* DEVICE STATUS */
bool WorkingSet::getLedG() {
    return false;
}
bool WorkingSet::getLedY() {
    return false;
}
bool WorkingSet::getLedR() {
    return false;
}
bool WorkingSet::getLedUV() {
    return false;
}
bool WorkingSet::getEngine() {
    return false;
}
bool WorkingSet::getFan() {
    return false;
}
int WorkingSet::getButton() {
    return BUTTON_NONE;
}

/* SENSORS DATA */
bool WorkingSet::getLimitSwitch() {
    return false;
}
float WorkingSet::getTemperature() {
    return 0.0;
}


Timer* WorkingSet::getTimer() {
    return _timer;
}
void WorkingSet::setTimer(Timer* timer) {
    delete _timer;
    _timer = timer;
}
