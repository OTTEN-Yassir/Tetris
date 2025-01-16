#include "Position.h"

Position::Position(int x, int y) : _pos(x, y) {}

int Position::getX() const {
    return _pos.first;
}

int Position::getY() const {
    return _pos.second;
}

void Position::setX(int x) {
    _pos.first = x;
}

void Position::setY(int y) {
    _pos.second = y;
}

bool Position::operator==(const Position &other) const {
    return _pos.first == other.getX() && _pos.second == other.getY();
}

Position operator+(const Direction2D &dir, const Position &p) {
    return {p.getX() + dir.first, p.getY() + dir.second};
}

Position operator+(const Position &p, const Direction2D &dir) {
    return dir + p;
}

Position operator-(const Position &p1, const Position &p2) {
    return {p1.getX() - p2.getX(), p1.getY() - p2.getY()};
}

std::ostream &operator<<(std::ostream &os, const Position &pos) {
    os << "(" << pos.getX() << ", " << pos.getY() << ")";
    return os;
}

Position &Position::operator=(const Position &other) {
    if (this != &other) {
        _pos.first = other._pos.first;
        _pos.second = other._pos.second;
    }
    return *this;
}

