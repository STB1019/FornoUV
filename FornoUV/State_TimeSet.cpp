#include "State_TimeSet.h"

const int State_TimeSet::cursorPos[][2] = {{1, 0}, {2, 0}, {4, 0}, {5, 0}, {0, 1}, {5, 1}};

// public
State_TimeSet::State_TimeSet() {
    setStateId(STATE_ID_TIMESET);
}
State_TimeSet::~State_TimeSet() {

}
void State_TimeSet::setup(State* prevState){
    WorkingSet* ws = WorkingSet::getInstance();
    // just came from IDLE: create the temporary timer (deleted in case of cancellation)
    if (prevState->equalId(STATE_ID_IDLE)) {
        ws->createTmpTimer();
    }
}

State* State_TimeSet::execute(State* prevState) {
    WorkingSet* ws = WorkingSet::getInstance();

    int button = ws->getButton();

    // nothing pressed: nothing to do
    if (button == BUTTON_NONE)
        return new State_TimeSet(_selected);

    // we proceed to the state IDLE, using (ok) or not (cancel) the new value
    if (button == BUTTON_SELECT) {
        bool confirmed = false;
        // ok
        if (_selected == 4) {
            confirmed = true;
            ws->confirmTmpTimer();
        }
        // cancel
        else if (_selected == 5) {
            confirmed = true;
            ws->rejectTmpTimer();
        }

        if (confirmed)
            return new State_Idle();
        else {
            return new State_TimeSet(_selected);
        }
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
        Timer* tt = ws->getTmpTimer();
        if (button == BUTTON_UP) {
            tt->incr(_selected, 1);
        }
        else if (button == BUTTON_DOWN) {
            tt->decr(_selected, 1);
        }
    }
    return new State_TimeSet(_selected);
}

// protected


// |----------------|
// |_hh:mm          |
// |>OK  >CANCEL    |
// |----------------|
void State_TimeSet::printLCD(LiquidCrystal lcd, State* prevState) {
    WorkingSet* ws = WorkingSet::getInstance();
    Timer* tt = ws->getTmpTimer();
    char* timestr = tt->getPrintable("@h:@m");


    bool printCursor = true;
    if (!this->equalState(prevState)) {
        lcd.clear();

        lcd.setCursor(1,1);
        lcd.print("OK");

        lcd.setCursor(6, 1);
        lcd.print("CANCEL");
    }
    else {
        if (prevState->getSelection() == _selected) {
            printCursor = false;
        }
    }


    if (printCursor) {
        int oldSel = prevState->getSelection();
        // selects one of the digits of the timer -> nothing
        // selects OK or CANCEL -> cleanup only needed if the previous state has the same type
        if (this->equalState(prevState) && oldSel >= 4) {
            lcd.setCursor(cursorPos[oldSel][0], cursorPos[oldSel][1]);
            lcd.print(' ');
        }

        // selects OK or CANCEL
        if (_selected >= 4) {
            lcd.setCursor(cursorPos[_selected][0], cursorPos[_selected][1]);
            lcd.print('>');
        }
    }

    // selects one of the digits of the timer -> nothing
    if (_selected <= 3) {
        if ((millis() / BLINK_TIME_OFF) % (1 + BLINK_TIME_ON / BLINK_TIME_OFF) == 0) {
            int index = (_selected < 2 ? _selected : _selected + 1);
            timestr[index] = ' ';
        }
    }

    lcd.setCursor(1, 0);
    lcd.print(timestr);
    free(timestr);
}

// private
State_TimeSet::State_TimeSet(int sel) : State_TimeSet::State_TimeSet() {
    _selected = sel;
}
