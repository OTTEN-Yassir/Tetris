#include <iostream>
#include "Game.h"
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>


Game::Game(int height, int width)
    : _board(Board(height, width)),
    _bag(),
    _score(0),
    _level(1),
    _speed(1000),
    _totalRowsCompleted(0),
    _isGameOver(false),
    _brickCpt(0),
    _isTickRunning(true){
    _bag.shuffle();
    _nextBrick = _bag.getBricks()[0];
    setCurrentBrick();
}

void Game::startTick(const UpdateCurrentThread& updateCurrentThread) {
    computeSpeed();
    auto downFunc = [this,updateCurrentThread]() {
        while (!_isGameOver && _isTickRunning) {
            std::this_thread::sleep_for(std::chrono::milliseconds(_speed));
            updateCurrentThread();// will call the lambda function in GameBoard and will emit the signal to move down the current brick in the current thread
        }
    };
    _tickThread = std::thread(downFunc);
}

void Game::stopTick() {
    _isTickRunning = false;
    if (_tickThread.joinable()) {
        _tickThread.join();
    }
}
void Game::move(const Direction2D &dir) {
    if (!_board.move(_currentBrick, dir)) {
        manageScoreAndRules(0);
    }
    Notify();
}

void Game::rotate(bool clockwise) {
    _board.rotateBrick(_currentBrick, clockwise);
    Notify();
}

void Game::checkGameOverRules() {
    if (isTimeUp() || _totalRowsCompleted >= MAX_ROWSCOMPLETED ||
        _score >= MAX_SCORE) {
        _board.setIsGameOver(true);
    }
}

void Game::manageScoreAndRules(int dropDistance) {
    int completed = deleteCompletedRows();

    if (completed > 0 || dropDistance > 0) {
        _totalRowsCompleted += completed;
        addScore(completed, dropDistance);
    }
    setCurrentBrick();
    checkGameOverRules();
}


void Game::drop() {
    auto initialPositions = _currentBrick.getVecPos();
    while (_board.move(_currentBrick, Direction::DOWN));
    int dropDistance = calculateDistanceDrop(initialPositions);
    manageScoreAndRules(dropDistance);
    Notify();
}


int Game::calculateDistanceDrop(const std::vector<Position> &initialPositions) {
    int dropDistance = 0;
    for (size_t i = 0; i < initialPositions.size(); ++i) {
        int initialRow = initialPositions[i].getX();
        int newRow = _currentBrick.getVecPos()[i].getX();
        int distance = newRow - initialRow;
        dropDistance = std::max(dropDistance, distance);
    }
    return dropDistance;
}

int Game::deleteCompletedRows() {
    int rowsCompleted = 0;
    for (size_t i = 0; i < _currentBrick.getVecPos().size(); ++i) {
        for (int row = _board.getHeight() - 1; row > 0; --row) {
            if (_board.isCompletedRow(row)) {
                _board.deleteRow(row);
                _board.dropRows(row);
                ++rowsCompleted;
            }
        }
    }
    return rowsCompleted;
}

bool Game::isTimeUp() {
    auto currentTime = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::minutes>(currentTime - _time);
    return duration.count() >= MAX_TIME;
}

void Game::startTime() {
    _time = std::chrono::steady_clock::now();
}

std::string Game::getTimeString() const {
    auto currentTime = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(currentTime - _time);
    int hours = duration.count() / 3600;
    int minutes = (duration.count() % 3600) / 60;
    int seconds = duration.count() % 60;

    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << hours << "h "
       << std::setfill('0') << std::setw(2) << minutes << "m "
       << std::setfill('0') << std::setw(2) << seconds << "s";

    return ss.str();
}

std::chrono::time_point<std::chrono::steady_clock> Game::getTime() const {
    return _time;
}

int Game::getScore() const {
    return _score;
}

int Game::getLevel() const {
    return _level;
}

int Game::getTotalRowsCompleted() const {
    return _totalRowsCompleted;
}

const Brick &Game::getCurrentBrick() const {
    return _currentBrick;
}

const Bag &Game::getBag() const {
    return _bag;
}

const Board &Game::getBoardGame() const {
    return _board;
}

void Game::setLevel(int level) {
    _level = level;
}

void Game::setScore(int score) {
    _score = score;
}

void Game::setSpeed(long speed) {
    _speed = speed;
}

void Game::setTotalRowsCompleted(int totalRowsCompleted) {
    _totalRowsCompleted = totalRowsCompleted;
}

void Game::setIsGameOver(bool b) {
    _board.setIsGameOver(b);
}

void Game::setCurrentBrick() {
    bool isPlacedAllBrick = _brickCpt % _bag.getBricks().size() == 0;

    _currentBrick = _nextBrick;
    _board.addBrick(_currentBrick);

    if (isPlacedAllBrick) {
        _brickCpt = 0;
        _bag.shuffle();
        _nextBrick = _bag.getBricks()[0];
    } else {
        int nextBrickIndex = (_brickCpt + 1) % _bag.getBricks().size();
        _nextBrick = _bag.getBricks()[nextBrickIndex];
    }

    ++_brickCpt;
}

void Game::setTime(std::chrono::time_point<std::chrono::steady_clock> time) {
    _time = time;
}

bool Game::isGameOver() {
    _isGameOver = _board.isGameOver();
    return _isGameOver;
}

void Game::addScore(int rowsCompleted, int dropDistance) {
    int scoreIncrease = 0;

    if (rowsCompleted <= 1) {
        scoreIncrease = ((40 * rowsCompleted) + dropDistance) * _level;
    } else if (rowsCompleted == 2) {
        scoreIncrease = ((100 * rowsCompleted) + dropDistance) * _level;
    } else if (rowsCompleted == 3) {
        scoreIncrease = ((300 * rowsCompleted) + dropDistance) * _level;
    } else if (rowsCompleted == 4) {
        scoreIncrease = ((1200 * rowsCompleted) + dropDistance) * _level;
    }

    if (_totalRowsCompleted % 10 == 0 && rowsCompleted > 0) {
        ++_level;
        if (_level < 20){
            computeSpeed();
        }
    }

    _score += scoreIncrease;

}

void Game::computeSpeed() {
    auto it = LEVEL_SPEED.find(_level);
    _speed = it->second;
}

int Game::getMAX_SCORE() {
    return MAX_SCORE;
}

int Game::getMAX_TIME() {
    return MAX_TIME;
}

int Game::getMAX_ROWSCOMPLETED() {
    return MAX_ROWSCOMPLETED;
}

int Game::getSpeed() {
    return _speed;
}

Brick Game::getNextBrick(){
    return _nextBrick;
}

void Game::fillBoardWithBricks(int density) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    int sequences = ((_board.getWidth() * _board.getHeight() * density) / 150) + 1;

    for (int i = 0; i < sequences; ++i) {
        Direction2D moveDirection = (std::rand() % 2) == 0 ? Direction::LEFT : Direction::RIGHT;

        int moves = std::rand() % (_board.getWidth() / 2 + 2);
        for (int j = 0; j < moves; ++j) {
            move(moveDirection);
        }

        move(Direction::DOWN);

        for (int j = 0; j < moves; ++j) {
            rotate(true);
        }

        drop();
    }
    _isGameOver = false;
    _board.setIsGameOver(false);
    _score = 0;
    _level = 1;
    _totalRowsCompleted = 0;
}

Game &Game::operator=(const Game &other) {
    if (this != &other) {
        _bag = other._bag;
        _board = other._board;
        _currentBrick = other._currentBrick;
        _isGameOver = other._isGameOver;
        _level = other._level;
        _score = other._score;
        _speed = other._speed;
        _brickCpt = other._brickCpt;
        _totalRowsCompleted = other._totalRowsCompleted;
    }

    return *this;
}
void Game::Attach(Observer *observer)
{
    Subject::observers_.insert(observer);
}

void Game::Detach(Observer *observer)
{
    auto it =observers_.find(observer);
    if (it != observers_.end()) {
        observers_.erase(it);
    }
}

void Game::Notify()const
{
    for (auto& obs : Subject::observers_) {
        obs->Update(this);
    }
}



