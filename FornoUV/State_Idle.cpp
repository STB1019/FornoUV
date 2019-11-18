#include "State_Idle.h"

// State_Idle::_selected = 0;

// public
State_Idle::State_Idle() {
    setStateId(STATE_ID_IDLE);
}
State_Idle::~State_Idle() {

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
        if (_selected == 1) nextSel = 1;
        else nextSel = 0;
    }
    else if (button == BUTTON_UP) {
        if (_selected == 2) nextSel = 2;
        else nextSel = 0;
    }
    else if (button == BUTTON_DOWN) {
        nextSel = 1;
    }
    return new State_Idle(nextSel);
}

// protected


//  suggested          original (& implemented)
// |----------------| |----------------|
// |>TIME hh:mm     | |>TIME   >START  |
// |>TEMP xx° >START| |>TEMP           |
// |----------------| |----------------|
void State_Idle::printLCD(LiquidCrystal lcd) {
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("TIME");
    lcd.setCursor(9, 0);
    lcd.print("START");
    lcd.setCursor(1,1);
    lcd.print("TEMP");

    int posCol = -1;
    int posRow = -1;
    switch (_selected) {
        case 0: // TIME
            posCol = 0;
            posRow = 0;
            break;
        case 1: // TEMP
            posCol = 0;
            posRow = 1;
            break;
        case 2: // START
            posCol = 8;
            posRow = 0;
            break;
        default:
            break;
    }

    if (posCol != -1) {
        lcd.setCursor(posCol, posRow);
        lcd.print(">");
    }
}

// private
State_Idle::State_Idle(int sel) : State_Idle::State_Idle() {
    _selected = sel;
}
