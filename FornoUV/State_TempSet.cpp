#include "State_TempSet.h"

// public
State_TempSet::State_TempSet() {

}
State_TempSet::~State_TempSet() {

}
State* State_TempSet::execute(State* prevState) {
    return new State_TempSet();
}

// protected
void State_TempSet::printLCD() {

}

// private
