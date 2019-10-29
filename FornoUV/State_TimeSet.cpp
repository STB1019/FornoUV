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
        _nextTimer = new Timer(ws->getTimer());
    }


    int button = ws->getButton();

    // nothing pressed: nothing to do
    if (button == BUTTON_NONE)
        return new State_TimeSet(this);

    // we proceed to the state IDLE, using (ok) or not (cancel) the new value
    if (button == BUTTON_SELECT) {
        // ok
        if (_selected == 4) {
            ws->setTimer(_nextTimer);
        }
        // cancel
        else if (_selected == 5) {
            delete _nextTimer;
        }

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
        State_TimeSet* next = new State_TimeSet(this);
        next->_selected = nextSel;
        return next;
    }

    // handle digit cycling
    if (_selected < 4) {
        if (button == BUTTON_UP) {
            // increase timer digit
        }
        else if (button == BUTTON_DOWN) {
            // decrease timer digit
        }
    }
    return new State_TimeSet(this);
}

// protected
void State_TimeSet::printLCD() {

}

// private
State_TimeSet::State_TimeSet(State_TimeSet* state) : State_TimeSet::State_TimeSet() {
    _nextTimer = state->_nextTimer;
    _selected = state->_selected;
}

State_TimeSet::State_TimeSet(Timer* nextTimer) : State_TimeSet::State_TimeSet() {
    _nextTimer = nextTimer;
}
