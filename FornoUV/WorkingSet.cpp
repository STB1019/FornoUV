#include "WorkingSet.h"

WorkingSet* WorkingSet::_instance = NULL;

WorkingSet* WorkingSet::getInstance() {
    if (_instance == NULL) {
        _instance = new WorkingSet();
    }
    return _instance;
}

WorkingSet::WorkingSet() {
    pinMode(PIN_BUTTON, INPUT);


    _ledGStatus = false;
    _ledYStatus = false;
    _ledRStatus = false;
    _ledUVStatus = false;

    _motorStatus = false;
    _fanStatus = false;

    readLimitSwitch();
    readTemperature();
    _timer = new Timer(0, 15, 0); // default: 15 minutes
    _targetTemp = 50; // default: 50°C
}

/* DEVICE STATUS */
void WorkingSet::setLedG(bool status) {
    _ledGStatus = status;
}
void WorkingSet::setLedY(bool status) {
    _ledYStatus = status;
}
void WorkingSet::setLedR(bool status) {
    _ledRStatus = status;
}
void WorkingSet::setLedUV(bool status) {
    _ledUVStatus = status;
}
void WorkingSet::setMotor(bool status) {
    _motorStatus = status;
}
void WorkingSet::setFan(bool status) {
    _fanStatus = status;
}
bool WorkingSet::getLedG() {
    return _ledGStatus;
}
bool WorkingSet::getLedY() {
    return _ledYStatus;
}
bool WorkingSet::getLedR() {
    return _ledRStatus;
}
bool WorkingSet::getLedUV() {
    return _ledUVStatus;
}
bool WorkingSet::getMotor() {
    return _motorStatus;
}
bool WorkingSet::getFan() {
    return _fanStatus;
}



/* SENSORS DATA */
void WorkingSet::readLimitSwitch() {
    //TODO
}
void WorkingSet::readTemperature() {
    //TODO
}
void WorkingSet::readButton() {
    _button = analogRead(PIN_BUTTON);
}

/* SENSORS GETTERS */
bool WorkingSet::getLimitSwitch() {
    return _limitSwitchStatus;
}
float WorkingSet::getTemperature() {
    return _temperature;
}
int WorkingSet::getButton() {
    int out = BUTTON_NONE; // 1023
    if (_button < 65)   out = BUTTON_RIGHT; // 0
    else if (_button < 220)  out = BUTTON_UP; // 130
    else if (_button < 400)  out = BUTTON_DOWN; // 305
    else if (_button < 600)  out = BUTTON_LEFT; // 479
    else if (_button < 850)  out = BUTTON_SELECT; // 720

    if (_buttonHeld == out) {
        return BUTTON_NONE;
    }
    else {
        _buttonHeld = out;
        return out;
    }
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
