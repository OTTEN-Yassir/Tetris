#include "Brick.h"

Brick::Brick(const Position &center, const std::vector<Position> &vecPos)
        : _center{center}, _vecPos{vecPos} {}

void Brick::rotate(bool clockwise) {
    for (auto &pos: _vecPos) {
        if (!clockwise) {
            int temp = pos.getX();
            pos.setX(-(pos.getY() - _center.getY()) + _center.getX());
            pos.setY(temp - _center.getX() + _center.getY());
        } else {
            int temp = pos.getX();
            pos.setX((pos.getY() - _center.getY()) + _center.getX());
            pos.setY(-(temp - _center.getX()) + _center.getY());
        }
    }
}

void Brick::move(const Direction2D &dir) {
    _center = _center + dir;
    for (auto &pos: _vecPos) {
        pos = pos + dir;
    }
}

std::vector<Position> Brick::getVecPos() const {
    return _vecPos;
}

const Position &Brick::getCenter() const {
    return _center;
}

void Brick::setCenter(const Position &pos) {
    _center.setX(pos.getX());
    _center.setY(pos.getY());
}

void Brick::setVecPos(const std::vector<Position> &vecPos) {
    _vecPos.clear();
    for (const auto &pos: vecPos) {
        _vecPos.push_back(pos);
    }
}

Brick &Brick::operator=(const Brick &other) {
    if (this != &other) {
        _center = other._center;
        _vecPos = other._vecPos;
    }
    return *this;
}

bool Brick::operator==(const Brick &other) const {
    return _center == other._center && _vecPos == other._vecPos;
}
