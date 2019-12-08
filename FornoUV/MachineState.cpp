#include "MachineState.h"

MachineState::MachineState(LiquidCrystal* lcd, void (*start)(MachineState*, LiquidCrystal*, int)) {
    /* this->_prevId = NO_STATE;
    this->_curr = NULL;
    this->_next = start; */
    this->_curr = NULL;
    this->doTransition(NO_STATE, start);
    this->_lcd = lcd;
}

MachineState::~MachineState() {

}

bool MachineState::doExecution() {
    if (this->_next != NULL) {
        this->_curr = this->_next; //State switch to the next to execute
        this->_next = NULL; //Sets the next state NULL (new value set into execution of actual state)
        this->_curr(this, this->_lcd, this->_prevId);
        return true;
    }
    return false;
}

void MachineState::setNextState(void (*next)(MachineState*, LiquidCrystal*, int)) {
    this->_next = next;
}

void MachineState::doTransition(int currId, void (*next)(MachineState*, LiquidCrystal*, int)) {
    this->_prevId = currId;
    this->setNextState(next);
}
