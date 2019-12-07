#include "MachineState.h"

void MachineState::execute_StateReady(MachineState* machine, LiquidCrystal* lcd, int prevStateId) {
    static int counter = 0;

    if (prevStateId != STATE_ID_READY)
        counter = 0;

    lcd->clear();
    lcd->setCursor(1,0);
    lcd->print("STATE: ");
    lcd->setCursor(8, 0);
    lcd->print(STATE_ID_READY);
    
    lcd->setCursor(1, 1);
    lcd->print(counter);
    counter++;
    delay(1000);

    if (counter == 5)
        machine->doTransition(STATE_ID_READY, STATE_WORKING);
    else
        machine->doTransition(STATE_ID_READY, STATE_READY);
}

/*

// public
State_Ready::State_Ready() {
    setStateId(STATE_ID_READY);
}
State_Ready::~State_Ready() {

}
void State_Ready::setup(State* prevState){
    
}
State* State_Ready::execute(State* prevState) {
    return new State_Ready();
}

// protected
void State_Ready::printLCD(LiquidCrystal lcd, State* prevState) {

}

// private
*/