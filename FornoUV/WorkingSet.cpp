#include "WorkingSet.h"

WorkingSet* WorkingSet::_instance = nullptr;

WorkingSet* WorkingSet::getInstance() {
    if (_instance == nullptr) {
        _instance = new WorkingSet();
    }
    return _instance;
}

WorkingSet::WorkingSet() {

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

/* SENSORS DATA */
bool WorkingSet::getLimitSwitch() {
    return false;
}
float WorkingSet::getTemperature() {
    return 0.0;
}