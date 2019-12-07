#include "MachineState.h"

MachineState::MachineState(LiquidCrystal* lcd, void (*start)(MachineState*, LiquidCrystal*, int)) {
    this->_prevId = NO_STATE;
    this->_curr = start;
    this->_next = NULL;
    this->_lcd = lcd;
}

MachineState::~MachineState() {

}

bool MachineState::doExecution() {
    if (this->_curr != NULL) {
        this->_curr(this, this->_lcd, this->_prevId);
        this->_curr = this->_next;
        this->_next = NULL;
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
