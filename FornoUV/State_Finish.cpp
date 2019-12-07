#include "MachineState.h"

void MachineState::execute_StateFinish(MachineState* machine, LiquidCrystal* lcd, int prevStateId) {
    static int counter = 0;

    if (prevStateId != STATE_ID_FINISH)
        counter = 0;

    lcd->clear();
    lcd->setCursor(1,0);
    lcd->print("STATE: ");
    lcd->setCursor(8, 0);
    lcd->print(STATE_ID_FINISH);
    
    lcd->setCursor(1, 1);
    lcd->print(counter);
    counter++;
    delay(1000);

    if (counter == 5)
        machine->doTransition(STATE_ID_FINISH, STATE_IDLE);
    else
        machine->doTransition(STATE_ID_FINISH, STATE_FINISH);
}

/*

// public
State_Finish::State_Finish() {
    setStateId(STATE_ID_FINISH);
}
State_Finish::~State_Finish() {

}
void State_Finish::setup(State* prevState){
    
}
State* State_Finish::execute(State* prevState) {
    return new State_Finish();
}

// protected
void State_Finish::printLCD(LiquidCrystal lcd, State* prevState) {

}

// private
*/