#include "MachineState.h"

void MachineState::execute_StatePreparation(MachineState* machine, LiquidCrystal* lcd, int prevStateId) {
    static int counter = 0;

    if (prevStateId != STATE_ID_PREPARATION)
        counter = 0;

    lcd->clear();
    lcd->setCursor(1,0);
    lcd->print("STATE: ");
    lcd->setCursor(8, 0);
    lcd->print(STATE_ID_PREPARATION);
    
    lcd->setCursor(1, 1);
    lcd->print(counter);
    counter++;
    delay(1000);

    if (counter == 5)
        machine->doTransition(STATE_ID_PREPARATION, STATE_READY);
    else
        machine->doTransition(STATE_ID_PREPARATION, STATE_PREPARATION);
}

/*
// public
State_Preparation::State_Preparation() {
    setStateId(STATE_ID_PREPARATION);
}
State_Preparation::~State_Preparation() {

}
void State_Preparation::setup(State* prevState){

}
State* State_Preparation::execute(State* prevState) {
    return new State_Preparation();
}

// protected
void State_Preparation::printLCD(LiquidCrystal lcd, State* prevState) {
    int index = (millis() / 25) % 32;
    int index2 = (index + 32 - 8) % 32;

    lcd.setCursor(index2 % 16, index2 / 16);
    lcd.print(' ');

    index++;
    index %= 32;
    lcd.setCursor(index % 16, index / 16);
    lcd.write((byte) 0);
}

// private
State_Preparation::State_Preparation(int sel) : State_Preparation::State_Preparation() {
    _selected = sel;
}
*/