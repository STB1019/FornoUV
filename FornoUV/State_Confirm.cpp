#include "State_Confirm.h"

// public
State_Confirm::State_Confirm() {

}
State_Confirm::~State_Confirm() {

}
State* State_Confirm::execute(State* prevState) {
    return new State_Confirm();
}

// protected
void State_Confirm::printLCD() {

}

// private
