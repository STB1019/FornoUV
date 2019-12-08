#include "MachineState.h"
#include "Trasductor.h"
#include "WorkingSet.h"
#include "utils.h"

#define TEMPSET_MENU_OK 0
#define TEMPSET_MENU_CANCEL 1

void MachineState::execute_StateTempset(MachineState* machine, LiquidCrystal* lcd, int prevStateId) {
    //                                      0: OK ;;; 1: CANCEL 
    static const int CURSOR_POSITIONS[][2] = {{0, 1}, {5, 1}};
    static WorkingSet* ws = WorkingSet::getInstance();
    static Trasductor* tras = Trasductor::getInstance();
    static int selected = 0;
    ExecStateFunct next = STATE_TEMPSET;
    char strtemp[3];

    /*Not autoring, so there's to set state for the first time*/
    if (prevStateId != STATE_ID_TEMPSET) {
        ws->createTmpTargetTemp();

        lcd->clear();
        selected = TEMPSET_MENU_OK;
        formatNum(strtemp, ws->getTmpTargetTemp(), 2);
        lcd->setCursor(1,0);
        lcd->print(strtemp);
        lcd->print((char)223); // °
        lcd->print('C');
        lcd->setCursor(CURSOR_POSITIONS[selected][0],CURSOR_POSITIONS[selected][1]);
        lcd->print(CURSOR);
        lcd->print("OK   CANCEL");
    }

    int button = tras->getButton();

    if (button != BUTTON_NONE) {
        // it proceeds to the state determined by _selected
        if (button == BUTTON_SELECT) {
            if (selected == TEMPSET_MENU_OK) {
                //confirms the new temperature setted into the state
                ws->confirmTmpTargetTemp();
            }
            else {// if (selected == TEMPSET_MENU_CANCEL) {
                //DO NOTHING
            }
            next = STATE_IDLE;
        }
        // handle movement in the menu:
        else {
            // |----------------|
            // |_xx°C           |
            // |>OK  >CANCEL    |
            // |----------------|
            if (button == BUTTON_RIGHT) {
                if (selected != TEMPSET_MENU_CANCEL) {
                    printMenuCursor(lcd, CURSOR_POSITIONS, selected, true); //erase old
                    selected = TEMPSET_MENU_CANCEL;
                    printMenuCursor(lcd, CURSOR_POSITIONS, selected, false); //print new
                }
            }
            else if (button == BUTTON_LEFT) {
                if (selected != TEMPSET_MENU_OK) {
                    printMenuCursor(lcd, CURSOR_POSITIONS, selected, true); //erase old
                    selected = TEMPSET_MENU_OK;
                    printMenuCursor(lcd, CURSOR_POSITIONS, selected, false); //print new
                }
            }
            else {
                //Actions on temperature
                int amnt = 0;

                if (button == BUTTON_UP) {
                    amnt = 1;
                }
                else if (button == BUTTON_DOWN) {
                    amnt = -1;
                }

                ws->changeTmpTargetTemp(amnt);
                formatNum(strtemp, ws->getTmpTargetTemp(), 2);
                lcd->setCursor(1,0);
                lcd->print(strtemp);
            }
        }
    }

    machine->doTransition(STATE_ID_TEMPSET, next);
}
