#include "WorkingSet.h"

WorkingSet* WorkingSet::_instance = nullptr;

WorkingSet* WorkingSet::getInstance() {
    if (_instance == nullptr) {
        _instance = new WorkingSet();
    }
    return _instance;
}

WorkingSet::WorkingSet() {
    _ledGStatus = false;
    _ledYStatus = false;
    _ledRStatus = false;
    _ledUVStatus = false;

    _motorStatus = false;
    _fanStatus = false;

    readLimitSwitch();
    readTemperature();
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
bool WorkingSet::getLimitSwitch() {
    return _limitSwitchStatus;
}
float WorkingSet::getTemperature() {
    return _temperature;
}