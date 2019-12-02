#include "State_Finish.h"

// public
State_Finish::State_Finish() {
    setStateId(STATE_ID_FINISH);
}
State_Finish::~State_Finish() {

}
void State_Finish::setup(State* prevState){

}
State* State_Finish::execute(State* prevState) {
    return new State_Finish();
}

// protected
void State_Finish::printLCD(LiquidCrystal lcd, State* prevState) {

}
void State_Finish::printLCDOpt(LCDOptimizer lcdOpt, State* prevState) {

}

// private
