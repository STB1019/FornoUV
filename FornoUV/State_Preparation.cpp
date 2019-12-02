#include "State_Preparation.h"

// public
State_Preparation::State_Preparation() {
    setStateId(STATE_ID_PREPARATION);
}
State_Preparation::~State_Preparation() {

}
void State_Preparation::setup(State* prevState){

}
State* State_Preparation::execute(State* prevState) {
    return new State_Preparation();
}

// protected
void State_Preparation::printLCD(LiquidCrystal lcd, State* prevState) {
    int index = (millis() / 25) % 32;
    int index2 = (index + 32 - 8) % 32;

    lcd.setCursor(index2 % 16, index2 / 16);
    lcd.print(' ');

    index++;
    index %= 32;
    lcd.setCursor(index % 16, index / 16);
    lcd.write((byte) 0);
}
void State_Preparation::printLCDOpt(LCDOptimizer lcdOpt, State* prevState) {

}

// private
State_Preparation::State_Preparation(int sel) : State_Preparation::State_Preparation() {
    _selected = sel;
}
