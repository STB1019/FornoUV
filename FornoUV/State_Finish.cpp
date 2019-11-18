#include "State_Finish.h"

// public
State_Finish::State_Finish() {
    setStateId(STATE_ID_FINISH);
}
State_Finish::~State_Finish() {

}
State* State_Finish::execute(State* prevState) {
    return new State_Finish();
}

// protected
void State_Finish::printLCD(LiquidCrystal lcd, State* prevState) {

}

// private
