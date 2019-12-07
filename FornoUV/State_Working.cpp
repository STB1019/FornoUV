#include "MachineState.h"

void MachineState::execute_StateWorking(MachineState* machine, LiquidCrystal* lcd, int prevStateId) {
    static int counter = 0;

    if (prevStateId != STATE_ID_WORKING)
        counter = 0;

    lcd->clear();
    lcd->setCursor(1,0);
    lcd->print("STATE: ");
    lcd->setCursor(8, 0);
    lcd->print(STATE_ID_WORKING);
    
    lcd->setCursor(1, 1);
    lcd->print(counter);
    counter++;
    delay(1000);

    if (counter == 5)
        machine->doTransition(STATE_ID_WORKING, STATE_FINISH);
    else
        machine->doTransition(STATE_ID_WORKING, STATE_WORKING);
}

/*

// public
State_Working::State_Working() {
    setStateId(STATE_ID_WORKING);
}
State_Working::~State_Working() {

}
void State_Working::setup(State* prevState){
    
}
State* State_Working::execute(State* prevState) {
    return new State_Working();
}

// protected
void State_Working::printLCD(LiquidCrystal lcd, State* prevState) {

}

// private
*/