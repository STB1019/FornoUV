#include "MachineState.h"
#include "Trasductor.h"
#include "WorkingSet.h"
#include "utils.h"

#define TIMESET_MENU_HSX 0
#define TIMESET_MENU_HDX 1
#define TIMESET_MENU_MSX 2
#define TIMESET_MENU_MDX 3
#define TIMESET_MENU_OK 4
#define TIMESET_MENU_CANCEL 5

#define BLINK_TIME_OFF  150
#define BLINK_TIME_ON   350
#define TIME_FORMAT "@h:@m"

void MachineState::execute_StateTimeset(MachineState* machine, LiquidCrystal* lcd, int prevStateId) {
    static int counter = 0;
    //                                      0: SX_HOUR ;;; 1: DX_HOUR ;;; 2: SX_MIN ;;; 3: DX_MIN ;;; 4: OK ;;; 5: CANCEL 
    static const int CURSOR_POSITIONS[][2] = {{1, 0}, {2, 0}, {4, 0}, {5, 0}, {0, 1}, {5, 1}};
    static WorkingSet* ws = WorkingSet::getInstance();
    static Trasductor* tras = Trasductor::getInstance();
    static int selected = 0;
    static char strtime[6];
    ExecStateFunct next = STATE_TIMESET;
    bool cursorOnADigit = false;
    bool blinkDigit = false;
    bool refreshPrinted = false;

    /*Not autoring, so there's to set state for the first time*/
    if (prevStateId != STATE_ID_TIMESET) {
        counter = 0;

        ws->createTmpTimer();

        lcd->clear();
        selected = TIMESET_MENU_MDX;
        /*First time need to be printed*/
        ws->getTmpTimer()->getStaticPrintable(TIME_FORMAT, strtime);
        lcd->setCursor(CURSOR_POSITIONS[TIMESET_MENU_HSX][0],CURSOR_POSITIONS[TIMESET_MENU_HSX][1]);
        lcd->print(strtime);
        lcd->setCursor(1,1);
        lcd->print("OK   CANCEL");
    }

    int button = tras->getButton();
    cursorOnADigit = selected >= TIMESET_MENU_HSX && selected <= TIMESET_MENU_MDX; //cursor is on a digit
    blinkDigit = cursorOnADigit;

    if (button != BUTTON_NONE) {
        // it proceeds to the state determined by selected
        if (button == BUTTON_SELECT) {
            if (selected == TIMESET_MENU_OK || cursorOnADigit) {
                //confirms the new time setted into the state
                ws->confirmTmpTimer();
            }
            else {// if (selected == TIMESET_MENU_CANCEL) {
                ws->rejectTmpTimer();
            }
            next = STATE_IDLE;
            refreshPrinted = false; //useless refresh printed timer
            blinkDigit = false; //useless blink digit
        }
        // handle movement in the menu:
        else {
            // |----------------|
            // |_hh:mm          |
            // |>OK  >CANCEL    |
            // |----------------|
            if (button == BUTTON_RIGHT) {
                if (selected == TIMESET_MENU_MDX) { //last digit --> goto OK
                    selected = TIMESET_MENU_OK;
                    printMenuCursor(lcd, CURSOR_POSITIONS, selected, false); //print new
                    refreshPrinted = true; //Needs to be refreshed printed to include the case blink has erased digit and now needs to be printed!
                    blinkDigit = false; //Stop blink digit
                }
                else if (selected == TIMESET_MENU_OK) {//OK --> goto CANCEL
                    printMenuCursor(lcd, CURSOR_POSITIONS, selected, true); //erase old
                    selected = TIMESET_MENU_CANCEL;
                    printMenuCursor(lcd, CURSOR_POSITIONS, selected, false); //print new
                    //refreshPrinted = false;    repetition: refreshPrinted is already false
                    //blinkDigit = false;       repetition: blinkDigit is already false
                }
                else if (cursorOnADigit) { //digit --> goto next digit
                    selected++;
                    refreshPrinted = true;    
                    //blinkDigit = true                repetition: blinkDigit is already true
                }
                else {//if (selected == TIMESET_MENU_CANCEL) {//CANCEL --> goto CANCEL
                    //DO NOTHING
                    //refreshPrinted = false;    repetition: refreshPrinted is already false
                    //blinkDigit = false;       repetition: blinkDigit is already false
                }
            }
            else if (button == BUTTON_LEFT) {
                if (selected == TIMESET_MENU_HSX) { //first digit --> goto first digit
                    //DO NOTHING
                    //blinkDigit = true;        repetition: blinkDigit is already true
                    //refreshPrinted = false;    repetition: refreshPrinted is already false
                }
                else if (cursorOnADigit) { //digit --> goto previous digit
                    selected--;
                    refreshPrinted = true; //Needs to be refreshed printed to include the case blink has erased digit and now needs to be printed!
                    //blinkDigit = true;        repetition: blinkDigit is already true
                }
                else if (selected == TIMESET_MENU_OK) {//OK --> goto last digit
                    printMenuCursor(lcd, CURSOR_POSITIONS, selected, true); //erase old
                    selected = TIMESET_MENU_MDX;
                    blinkDigit = true; //needs to manage blink
                    //refreshPrinted = false;    repetition: refreshPrinted is already false
                }
                else {//if (selected == TIMESET_MENU_CANCEL) {//CANCEL --> goto OK
                    printMenuCursor(lcd, CURSOR_POSITIONS, selected, true); //erase old
                    selected = TIMESET_MENU_OK;
                    printMenuCursor(lcd, CURSOR_POSITIONS, selected, false); //print new
                    //refreshPrinted = false;    repetition: refreshPrinted is already false
                    //blinkDigit = false;       repetition: blinkDigit is already false
                }
            }
            else {
                if (cursorOnADigit) {
                    //Actions on time
                    if (button == BUTTON_UP) {
                        ws->getTmpTimer()->incr(selected, 1);
                    }
                    else {//if (button == BUTTON_DOWN) {
                        ws->getTmpTimer()->decr(selected, 1);
                    }
                    refreshPrinted = true; //Needs to refresh with new value
                    //blinkDigit = true;        repetition: blinkDigit is already true
                }
                else {
                    //Move to timer
                    if (button == BUTTON_UP) {
                        printMenuCursor(lcd, CURSOR_POSITIONS, selected, true); //erase old
                        selected = TIMESET_MENU_MDX;
                        blinkDigit = true; //needs to manage blink
                        //refreshPrinted = false;    repetition: refreshPrinted is already false
                    }
                    else { //if (button == BUTTON_DOWN) {
                        //DO NOTHING
                    }
                }
            }
        }
    }

    /*Every time needs to be refreshed the printed timer*/
    if (refreshPrinted) {
        ws->getTmpTimer()->getStaticPrintable(TIME_FORMAT, strtime);
        lcd->setCursor(CURSOR_POSITIONS[TIMESET_MENU_HSX][0],CURSOR_POSITIONS[TIMESET_MENU_HSX][1]);
        lcd->print(strtime);
    }

    /*Every time needs to be managed blink on a digit*/
    if (blinkDigit) {
        //managing blink on the string to print. Index of string is the index of the digit into a string: "xx:xx"
        printMenuCursor(lcd, CURSOR_POSITIONS, selected, false, true, BLINK_TIME_ON, BLINK_TIME_OFF, strtime[selected < 2 ? selected : selected + 1]);
    }

    machine->doTransition(STATE_ID_TIMESET, next);
}

/*

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
*/