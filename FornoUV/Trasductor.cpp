#include "Trasductor.h"

Trasductor Trasductor::_instance;

Trasductor* Trasductor::getInstance() {
    return &_instance;
}

Trasductor::Trasductor() {
    pinMode(PIN_BUTTON, INPUT);

    /*
    readLimitSwitch();
    readTemperature();
    readButton();
    */
    this->_button = 1024;
    this->_buttonHeld = BUTTON_NONE;
}

/* SENSORS DATA */
void Trasductor::readLimitSwitch() {
    //TODO davvero?
}
void Trasductor::readTemperature() {
    //TODO
}
void Trasductor::readButton() {
    _button = analogRead(PIN_BUTTON);
}

/* SENSORS GETTERS */
bool Trasductor::getLimitSwitch() {
    return _limitSwitchStatus;
}
float Trasductor::getTemperature() {
    return _temperature;
}
int Trasductor::getButton() {
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
