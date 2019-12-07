#include "Actuator.h"

Actuator Actuator::_instance; //TODO test

Actuator* Actuator::getInstance() {
    return &_instance;
}

Actuator::Actuator() {
    _ledGStatus = false;
    _ledYStatus = false;
    _ledRStatus = false;
    _ledUVStatus = false;
    _motorStatus = false;
    _fanStatus = false;
}

void Actuator::inhibitFromInterrupt(bool inhibite) {
    this->_inhibitedByInterrupt = inhibite;
}

bool Actuator::isInhibitedByInterrupt() {
    return this->_inhibitedByInterrupt;
}

/* ACTUATE DEVICE */
void Actuator::setLedG(bool status) {
    _ledGStatus = status;
    //TODO
}
void Actuator::setLedY(bool status) {
    _ledYStatus = status;
    //TODO
}
void Actuator::setLedR(bool status) {
    _ledRStatus = status;
    //TODO
}
void Actuator::setLedUV(bool status) {
    _ledUVStatus = status;
    //TODO
}
void Actuator::setMotor(bool status) {
    _motorStatus = status;
    //TODO
}
void Actuator::setFan(bool status) {
    _fanStatus = status;
    //TODO
}

/* RETURN DEVICE */
bool Actuator::getLedG() {
    return _ledGStatus;
}
bool Actuator::getLedY() {
    return _ledYStatus;
}
bool Actuator::getLedR() {
    return _ledRStatus;
}
bool Actuator::getLedUV() {
    return _ledUVStatus;
}
bool Actuator::getMotor() {
    return _motorStatus;
}
bool Actuator::getFan() {
    return _fanStatus;
}
