#include "State_TimeSet.h"

// public
State_TimeSet::State_TimeSet() {

}
State_TimeSet::~State_TimeSet() {

}
State* State_TimeSet::execute(State* prevState) {
    return new State_TimeSet();
}

// protected
void State_TimeSet::printLCD() {

}

// private
