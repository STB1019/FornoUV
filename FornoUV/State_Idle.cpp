#include "MachineState.h"
#include "Trasductor.h"
#include "utils.h"

#define IDLE_MENU_TIME 0
#define IDLE_MENU_TEMP 1
#define IDLE_MENU_START 2

void MachineState::execute_StateIdle(MachineState* machine, LiquidCrystal* lcd, int prevStateId) {
    //                                      0: TIME ;;; 1: TEMP ;;; 2: START
    static const int CURSOR_POSITIONS[][2] = {{0,0}, {0,1}, {8,1}};
    static Trasductor* tras = Trasductor::getInstance();
    static int selected = 0;
    ExecStateFunct next = STATE_IDLE;

    /*Not autoring, so there's to set state for the first time*/
    if (prevStateId != STATE_ID_IDLE) {
        lcd->clear();
        selected = IDLE_MENU_TIME;
        lcd->setCursor(CURSOR_POSITIONS[selected][0],CURSOR_POSITIONS[selected][1]);
        lcd->print(CURSOR);
        lcd->print("TIME");
        lcd->setCursor(1,1);
        lcd->print("TEMP    START");
    }

    int button = tras->getButton();
    
    if (button != BUTTON_NONE) {
        // it proceeds to the state determined by _selected
        if (button == BUTTON_SELECT) {
            if (selected == IDLE_MENU_TIME) {
                next = STATE_TIMESET;
            }
            else if (selected == IDLE_MENU_TEMP) {
                next = STATE_TEMPSET;
            }
            else { //start
                next = STATE_CONFIRM;
            }
        }
        // handle movement in the menu:
        else {
            //  suggested         implemented
            // |----------------| |----------------|
            // |>TIME hh:mm     | |>TIME           |
            // |>TEMP xx° >START| |>TEMP   >START  |
            // |----------------| |----------------|
            if (button == BUTTON_RIGHT) {
                if (selected != IDLE_MENU_START) {
                    printMenuCursor(lcd, CURSOR_POSITIONS, selected, true); //erase old
                    selected = IDLE_MENU_START;
                    printMenuCursor(lcd, CURSOR_POSITIONS, selected, false); //print new
                }
            }
            else if (button == BUTTON_LEFT) {
                if (selected != IDLE_MENU_TIME && selected != IDLE_MENU_TEMP) {
                    printMenuCursor(lcd, CURSOR_POSITIONS, selected, true); //erase old
                    selected = IDLE_MENU_TEMP;
                    printMenuCursor(lcd, CURSOR_POSITIONS, selected, false); //print new
                }
            }
            else if (button == BUTTON_UP) {
                if (selected != IDLE_MENU_TIME) {
                    printMenuCursor(lcd, CURSOR_POSITIONS, selected, true); //erase old
                    selected = IDLE_MENU_TIME;
                    printMenuCursor(lcd, CURSOR_POSITIONS, selected, false); //print new
                }
            }
            else if (button == BUTTON_DOWN) {
                if (selected != IDLE_MENU_TEMP && selected != IDLE_MENU_START) {
                    printMenuCursor(lcd, CURSOR_POSITIONS, selected, true); //erase old
                    selected = IDLE_MENU_TEMP;
                    printMenuCursor(lcd, CURSOR_POSITIONS, selected, false); //print new
                }
            }
        }
    }

    machine->doTransition(STATE_ID_IDLE, next);
}