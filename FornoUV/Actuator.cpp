#include "Actuator.h"

Actuator* Actuator::_instance = NULL;

Actuator* Actuator::getInstance() {
    if (_instance == NULL) {
        _instance = new Actuator();
    }
    return _instance;
}

Actuator::Actuator() {

}

/* ACTUATE DEVICE */
void Actuator::setLedG(bool status) {

}
void Actuator::setLedY(bool status) {

}
void Actuator::setLedR(bool status) {

}
void Actuator::setLedUV(bool status) {

}
void Actuator::setEngine(bool status) {

}
void Actuator::setFan(bool status) {

}
