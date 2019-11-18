#include "State_TimeSet.h"

// public
State_TimeSet::State_TimeSet() {
    setStateId(STATE_ID_TIMESET);
}
State_TimeSet::~State_TimeSet() {

}
State* State_TimeSet::execute(State* prevState) {
    WorkingSet* ws = WorkingSet::getInstance();

    int prevStateId = prevState->getStateId();

    // just came from IDLE: create the temporary timer (deleted in case of cancellation)
    if (prevStateId == STATE_ID_IDLE) {
        ws->createTempTimer();
    }


    int button = ws->getButton();

    // nothing pressed: nothing to do
    if (button == BUTTON_NONE)
        return new State_TimeSet(_selected);

    // we proceed to the state IDLE, using (ok) or not (cancel) the new value
    if (button == BUTTON_SELECT) {
        // ok
        if (_selected == 4)
            ws->confirmTempTimer();
        // cancel
        else if (_selected == 5)
            ws->rejectTempTimer();

        return new State_Idle();
    }

    // handle movement in the menu:
    // > ok (0)  > cancel (1)
    int nextSel = -1;
    if (button == BUTTON_RIGHT) {
        nextSel = _selected < 5 ? _selected + 1 : _selected;
    }
    else if (button == BUTTON_LEFT) {
        nextSel = _selected > 0 ? _selected - 1 : _selected;
    }

    if (nextSel != -1) {
        return new State_TimeSet(nextSel);
    }

    // handle digit cycling
    // hh:mm (selected 0-3);
    if (_selected < 4) {
        Timer* tt = ws->getTempTimer();
        if (button == BUTTON_UP) {
            tt->incr(_selected, 1);
        }
        else if (button == BUTTON_DOWN) {
            tt->dect(_selected, 1);
        }
    }
    return new State_TimeSet(_selected);
}

// protected
void State_TimeSet::printLCD() {

}

// private
State_TimeSet::State_TimeSet(int selected) : State_TimeSet::State_TimeSet() {
    _selected = selected;
}
