#include "MachineState.h"

void MachineState::execute_StateConfirm(MachineState* machine, LiquidCrystal* lcd, int prevStateId) {

}

/*
const int State_Confirm::cursorPos[][2] = {{10, 1}, {14, 1}};

// public
State_Confirm::State_Confirm() {
    setStateId(STATE_ID_CONFIRM);
}
State_Confirm::~State_Confirm() {

}
void State_Confirm::setup(State* prevState){

}
State* State_Confirm::execute(State* prevState) {
    WorkingSet* ws = WorkingSet::getInstance();

    int button = ws->getButton();

    if (button == BUTTON_SELECT) {
        // yes
        if (_selected == 0)
            return new State_Preparation();

        if (_selected == 1)
            return new State_Idle();
    }

    int newSel = _selected;
    if (button == BUTTON_RIGHT)
        newSel = 1;
    else if (button == BUTTON_LEFT)
        newSel = 0;

    return new State_Confirm(newSel);
}

// protected


// |----------------|
// |_xx°C     _hh:mm|
// |CONFIRM?  >Y  >N|
// |----------------|
void State_Confirm::printLCD(LiquidCrystal lcd, State* prevState) {


    bool printCursor = true;
    if (!this->equalState(prevState)) {
        lcd.clear();

        // celsius sign
        lcd.setCursor(3, 0);
        lcd.print((char)223); // °
        lcd.print('C');

        lcd.setCursor(0, 1);
        lcd.print("CONFIRM?");

        lcd.setCursor(11, 1);
        lcd.print("Y");

        lcd.setCursor(15, 1);
        lcd.print("N");

        // print time and temperature
        WorkingSet* ws = WorkingSet::getInstance();
        Timer* tt = ws->getTimer();
        char* timestr = tt->getPrintable("@h:@m");

        int temp = (int) ws->getTargetTemp();
        char* tempstr = (char*) malloc(3 * sizeof(char));
        formatNum(tempstr, temp, 2);

        lcd.setCursor(1, 0);
        lcd.print(tempstr);
        free(tempstr);

        lcd.setCursor(6, 0);
        lcd.print(timestr);
        free(timestr);
    }
    else {
        if (prevState->getSelection() == _selected) {
            printCursor = false;
        }
    }


    if (printCursor) {
        int oldSel = prevState->getSelection();
        // delete old selection
        if (this->equalState(prevState)) {
            lcd.setCursor(cursorPos[oldSel][0], cursorPos[oldSel][1]);
            lcd.print(' ');
        }

        // print new cursor
        lcd.setCursor(cursorPos[_selected][0], cursorPos[_selected][1]);
        lcd.print('>');
    }
}

// private
State_Confirm::State_Confirm(int sel) : State_Confirm::State_Confirm() {
    _selected = sel;
}
*/