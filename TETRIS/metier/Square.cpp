#include "Square.h"

Square::Square(bool isOccupied) : _isOccupied(isOccupied) {}

bool Square::getIsOccupied() const {
    return _isOccupied;
}

void Square::setIsOccupied(bool isOccupied) {
    _isOccupied = isOccupied;
}
