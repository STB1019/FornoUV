#include "State_Error.h"

// public
State_Error::State_Error() {
    setStateId(STATE_ID_ERROR);
}
State_Error::~State_Error() {

}
void State_Error::setup(State* prevState){

}
State* State_Error::execute(State* prevState) {
    return new State_Error();
}

// protected
void State_Error::printLCD(LiquidCrystal lcd, State* prevState) {

}
void State_Error::printLCDOpt(LCDOptimizer* lcdOpt, State* prevState) {

}

// private
