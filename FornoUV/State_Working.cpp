#include "State_Working.h"

// public
State_Working::State_Working() {
    setStateId(STATE_ID_WORKING);
}
State_Working::~State_Working() {

}
State* State_Working::execute(State* prevState) {
    return new State_Working();
}

// protected
void State_Working::printLCD() {

}

// private
