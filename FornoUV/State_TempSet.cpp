#include "State_TempSet.h"

const int State_TempSet::cursorPos[][2] = {{0, 1}, {5, 1}};

// public
State_TempSet::State_TempSet() {
    setStateId(STATE_ID_TEMPSET);
}
State_TempSet::~State_TempSet() {

}
void State_TempSet::setup(State* prevState){
    WorkingSet* ws = WorkingSet::getInstance();

    // just came from IDLE: create temporary target temperature value (deleted in case of cancellation)
    if (prevState->equalId(STATE_ID_IDLE)) {
        ws->createTmpTargetTemp();
    }
}

State* State_TempSet::execute(State* prevState) {
    WorkingSet* ws = WorkingSet::getInstance();

    int button = ws->getButton();

    // nothing pressed: nothing to do
    if (button == BUTTON_NONE)
        return new State_TempSet(_selected);

    // we proceed to the state IDLE, using (ok) or not (cancel) the new value
    if (button == BUTTON_SELECT) {
        // ok
        if (_selected == 0)
            ws->confirmTmpTargetTemp();
        // cancel: nothing to reject

        return new State_Idle();
    }

    // handle movement in the menu:
    // > ok (0)  > cancel (1)
    int nextSel = -1;
    if (button == BUTTON_RIGHT) {
        nextSel = _selected < 1 ? _selected + 1 : _selected;
    }
    else if (button == BUTTON_LEFT) {
        nextSel = _selected > 0 ? _selected - 1 : _selected;
    }

    if (nextSel != -1) {
        return new State_TempSet(nextSel);
    }

    int changeAmt = 0;
    if (button == BUTTON_UP)
        changeAmt = 1;
    else if (button == BUTTON_DOWN)
        changeAmt = -1;

    if (changeAmt != 0)
        ws->changeTmpTargetTemp(changeAmt);

    return new State_TempSet(_selected);
}

// protected


// |----------------|
// |_xx°C           |
// |>OK  >CANCEL    |
// |----------------|
void State_TempSet::printLCD(LiquidCrystal lcd, State* prevState) {
    WorkingSet* ws = WorkingSet::getInstance();
    int temp = (int) ws->getTmpTargetTemp();
    char* tempstr = (char*) malloc(3 * sizeof(char));
    formatNum(tempstr, temp, 2);

    bool printCursor = true;
    if (!this->equalState(prevState)) {
        lcd.clear();

        lcd.setCursor(1,1);
        lcd.print("OK");

        lcd.setCursor(6, 1);
        lcd.print("CANCEL");

        lcd.setCursor(3, 0);
        lcd.print((char)223); // °
        lcd.print('C');

    }
    else {
        if (prevState->getSelection() == _selected) {
            printCursor = false;
        }
    }

    if (printCursor) {
        int oldSel = prevState->getSelection();
        // cleanup only needed if the previous state has the same type
        if (this->equalState(prevState)) {
            lcd.setCursor(cursorPos[oldSel][0], cursorPos[oldSel][1]);
            lcd.print(' ');
        }

        // selects OK or CANCEL
        lcd.setCursor(cursorPos[_selected][0], cursorPos[_selected][1]);
        lcd.print('>');
    }



    lcd.setCursor(1, 0);
    lcd.print(tempstr);
    free(tempstr);
}
void State_TempSet::printLCDOpt(LCDOptimizer* lcdOpt, State* prevState) {

}

// private
State_TempSet::State_TempSet(int sel) : State_TempSet::State_TempSet() {
    _selected = sel;
}
