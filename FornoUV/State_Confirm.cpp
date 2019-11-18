#include "State_Confirm.h"

// public
State_Confirm::State_Confirm() {
    setStateId(STATE_ID_CONFIRM);
}
State_Confirm::~State_Confirm() {

}
void State_Confirm::setup(State* prevState){
    
}
State* State_Confirm::execute(State* prevState) {
    return new State_Confirm();
}

// protected
void State_Confirm::printLCD(LiquidCrystal lcd, State* prevState) {

}

// private
