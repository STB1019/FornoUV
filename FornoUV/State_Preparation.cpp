#include "State_Preparation.h"

// public
State_Preparation::State_Preparation() {

}
State_Preparation::~State_Preparation() {

}
State* State_Preparation::execute(State* prevState) {
    return new State_Preparation();
}

// protected
void State_Preparation::printLCD() {

}

// private
