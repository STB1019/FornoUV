#include "State_Working.h"

// public
State_Working::State_Working() {
    setStateId(STATE_ID_WORKING);
}
State_Working::~State_Working() {

}
void State_Working::setup(State* prevState){

}
State* State_Working::execute(State* prevState) {
    return new State_Working();
}

// protected
void State_Working::printLCD(LiquidCrystal lcd, State* prevState) {

}
void State_Working::printLCDOpt(LCDOptimizer lcdOpt, State* prevState) {

}

// private
