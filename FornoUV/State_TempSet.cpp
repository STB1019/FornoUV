#include "State_TempSet.h"

// public
State_TempSet::State_TempSet() {
    setStateId(STATE_ID_TEMPSET);
}
State_TempSet::~State_TempSet() {

}
State* State_TempSet::execute(State* prevState) {
    WorkingSet* ws = WorkingSet::getInstance();

    int prevStateId = prevState->getStateId();

    // just came from IDLE: create temporary target temperature value (deleted in case of cancellation)
    if (prevStateId == STATE_ID_IDLE) {
        ws->createTempTargetTemp();
    }


    int button = ws->getButton();

    // nothing pressed: nothing to do
    if (button == BUTTON_NONE)
        return new State_TempSet(_selected);

    // we proceed to the state IDLE, using (ok) or not (cancel) the new value
    if (button == BUTTON_SELECT) {
        // ok
        if (_selected == 0)
            ws->confirmTempTargetTemp();
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
    if (button == BUTTON_DOWN)
        changeAmt = -1;

    if (changeAmt != 0)
        ws->changeTempTargetTemp(changeAmt);

    return new State_TempSet(_selected);
}

// protected
void State_TempSet::printLCD(LiquidCrystal lcd) {

}

// private
State_TempSet::State_TempSet(int selected) : State_TempSet::State_TempSet() {
    _selected = selected;
}
