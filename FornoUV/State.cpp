#include "State.h"

// public
int State::getStateId() {
    return _id;
}

int State::getSelection() {
    return _selected;
}

bool State::equalId(int id) {
    return _id == id;
}

// protected
void State::setStateId(int id) {
    _id = id;
}
bool State::equalState(State* prevState) {
    if (prevState == NULL) {
        return false;
    }

    if (this->getStateId() != prevState->getStateId()) {
        return false;
    }
    return true;
}

// private
