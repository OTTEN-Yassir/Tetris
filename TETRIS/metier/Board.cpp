#include "Board.h"
#include "DefaultBricks.h"
#include <chrono>

Board::Board(int height, int width) : _height(height), _width(width) {
    _isGameOver = false;
    _board.resize(_height);
    for (int y = 0; y < _height; ++y) {
        _board[y].resize(_width);
        for (int x = 0; x < _width; ++x) {
            _board[y][x] = std::make_unique<Square>(false);
        }
    }
}

bool Board::move(Brick &currentBrick, const Direction2D &dir) {
    bool canMoveDown;
    pickBrick(currentBrick);
    if (checkMove(currentBrick, dir)) {
        currentBrick.move(dir);
    }
    canMoveDown = checkMove(currentBrick, Direction::DOWN);
    placeBrick(currentBrick);
    return canMoveDown;
}

bool Board::rotateBrick(Brick &currentBrick, bool clockwise) {
    Brick tmp(currentBrick);
    tmp.rotate(clockwise);

    pickBrick(currentBrick);
    if (checkRotating(currentBrick, tmp)) {
        currentBrick.rotate(clockwise);
        placeBrick(currentBrick);
        return true;
    }
    return false;
}

bool Board::checkRotating(Brick &currentBrick, Brick &tmp) {
    for (const auto &pos: tmp.getVecPos()) {
        if (!isValidMove(pos)) {
            for (const auto &oldpos: currentBrick.getVecPos()) {
                _board[oldpos.getX()][oldpos.getY()]->setIsOccupied(true);
            }
            return false;
        }
    }
    return true;
}

void Board::addBrick(Brick &currentBrick) {
    int startY = (_width - 1) / 2;
    std::vector<Position> vec{};
    Position center(currentBrick.getVecPos()[0].getX(), startY);
    bool placeAvailable = true;
    for (const auto &pos: currentBrick.getVecPos()) {
        int x = pos.getX();
        int y = startY + pos.getY();

        Position newPos(x, y);
        if (!isValidMove(newPos)) {
            placeAvailable = false;
            setIsGameOver(true);
            break;
        }
    }

    if (placeAvailable) {
        for (const auto &pos: currentBrick.getVecPos()) {
            int x = pos.getX();
            int y = startY + pos.getY();
            _board[x][y]->setIsOccupied(true);
            vec.emplace_back(x, y);
        }
        currentBrick.setCenter(center);
        currentBrick.setVecPos(vec);
    }
}

void Board::placeBrick(const Brick &currentBrick) {
    for (const auto &oldpos: currentBrick.getVecPos()) {
        _board[oldpos.getX()][oldpos.getY()]->setIsOccupied(true);
    }
}

bool Board::checkMove(Brick &currentBrick, const Direction2D &dir) {
    for (const auto &pos: currentBrick.getVecPos()) {
        Position newPos(pos.getX() + dir.first, pos.getY() + dir.second);
        if (!isValidMove(newPos)) {
            return false;
        }
    }
    return true;
}

void Board::pickBrick(const Brick &currentBrick) {
    for (const auto &pos: currentBrick.getVecPos()) {
        _board[pos.getX()][pos.getY()]->setIsOccupied(false);
    }
}

bool Board::isValidMove(const Position &newPos) const {
    if (newPos.getX() < 0 || newPos.getY() < 0 || newPos.getX() >= _height || newPos.getY() >= _width) {
        return false;
    }

    if (_board[newPos.getX()][newPos.getY()]->getIsOccupied()) {
        return false;
    }
    return true;
}

bool Board::isCompletedRow(int row) {
    for (int j = 0; j < _width; ++j) {
        if (!_board[row][j]->getIsOccupied()) {
            return false;
        }
    }
    return true;
}


void Board::deleteRow(int row) {
    for (int j = 0; j < _width; ++j) {
        _board[row][j]->setIsOccupied(false);
    }
}


void Board::dropRows(int maxRows) {
    for (int i = maxRows; i > 0; --i) {
        swap(_board[i], _board[i - 1]);
    }
}

int Board::getHeight() const {
    return _height;
}


int Board::getWidth() const {
    return _width;
}


const std::vector<std::vector<std::unique_ptr<Square>>> &Board::getBoard() const {
    return _board;
}

bool Board::isGameOver() const {
    return _isGameOver;
}

void Board::setIsGameOver(bool isGameOver) {
    _isGameOver = isGameOver;
}

Board &Board::operator=(const Board &other) {
    if (this != &other) {
        _height = other._height;
        _width = other._width;

        _board.clear();

        _board.resize(_height);
        for (int y = 0; y < _height; ++y) {
            _board[y].resize(_width);
            for (int x = 0; x < _width; ++x) {
                _board[y][x] = std::make_unique<Square>(other._board[y][x]->getIsOccupied());
            }
        }
    }
    return *this;
}
