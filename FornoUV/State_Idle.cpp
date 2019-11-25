#include "State_Idle.h"

const int State_Idle::cursorPos[][2] = {{0, 0}, {0, 1}, {8, 1}};

// public
State_Idle::State_Idle() {
    setStateId(STATE_ID_IDLE);
}
State_Idle::~State_Idle() {

}
void State_Idle::setup(State* prevState){

}
State* State_Idle::execute(State* prevState) {
    WorkingSet* ws = WorkingSet::getInstance();

    int button = ws->getButton();

    if (button == BUTTON_NONE)
        return new State_Idle(_selected);

    // we proceed to the state determined by _selected
    if (button == BUTTON_SELECT) {
        // time
        if (_selected == 0)
            return new State_TimeSet();

        // temp
        if (_selected == 1)
            return new State_TempSet();

        // start
        if (_selected == 2)
            return new State_Confirm();
    }

    // handle movement in the menu:
    // > time (0)  > start (2)
    // > temp (1)
    int nextSel = -1;
    if (button == BUTTON_RIGHT) {
        nextSel = 2;
    }
    else if (button == BUTTON_LEFT) {
        if (_selected == 0) nextSel = 0;
        else nextSel = 1;
    }
    else if (button == BUTTON_UP) {
        nextSel = 0;
    }
    else if (button == BUTTON_DOWN) {
        if (_selected == 2) nextSel = 2;
        else nextSel = 1;
    }
    return new State_Idle(nextSel);
}

// protected


//  suggested          original (& implemented)
// |----------------| |----------------| |----------------|
// |>TIME hh:mm     | |>TIME   >START  | |>TIME           |
// |>TEMP xx° >START| |>TEMP           | |>TEMP   >START  |
// |----------------| |----------------| |----------------|
void State_Idle::printLCD(LiquidCrystal lcd, State* prevState) {


    bool printCursor = true;
    if (!this->equalState(prevState)) {
        lcd.clear();
        lcd.setCursor(1,0);
        lcd.print("TIME");
        lcd.setCursor(9, 1);
        lcd.print("START");
        lcd.setCursor(1,1);
        lcd.print("TEMP");
    }
    else if (prevState != NULL) {
        if (prevState->getSelection() == _selected)
            printCursor = false;
    }


    if (printCursor) {
        if (this->equalState(prevState)) {
            int oldSel = prevState->getSelection();
            lcd.setCursor(cursorPos[oldSel][0], cursorPos[oldSel][1]);
            lcd.print(' ');
        }

        lcd.setCursor(cursorPos[_selected][0], cursorPos[_selected][1]);
        lcd.print('>');
    }

    // lcd.setCursor(10, 1);
    // lcd.print(_selected);


}

// private
State_Idle::State_Idle(int sel) : State_Idle::State_Idle() {
    _selected = sel;
}
