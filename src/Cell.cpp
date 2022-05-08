#include "Cell.hpp"

Cell::Cell() {
    state = 0;
}

int Cell::GetState() const {
    return state;
}

void Cell::Die() {
    state = 0;
}

void Cell::Revive() {
    state = 1;
}