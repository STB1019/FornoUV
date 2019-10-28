#include "State_Idle.h"

// public
State_Idle::State_Idle() {
    setStateId(STATE_ID_IDLE);
}
State_Idle::~State_Idle() {

}
State* State_Idle::execute(State* prevState) {
    return new State_Idle();
}

// protected
void State_Idle::printLCD() {

}

// private
