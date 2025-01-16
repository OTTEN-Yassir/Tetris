#include "Controller.h"
#include <algorithm>

Controller::Controller(View view) : _view(view) {}

void Controller::start() {
    _view.displayTitle();

    if (_view.wantUpdateSize()) {
        std::pair<int, int> size;
        size = _view.askSize();
        _game = Game(size.first, size.second);
    }

    if (_view.wantPreFillBoard()) {
        int density = _view.askDensity();
        _game.fillBoardWithBricks(density);
    }

    if (_view.wantChangeLevel()) {
        int level = _view.askLevel();
        _game.setLevel(level);
    }

    _game.Attach(this);

    _game.startTime();

    _view.displayTitle();
    _view.displayBoard(_game);
    _view.displayLevelScore(_game.getLevel(), _game.getScore(), _game.getTotalRowsCompleted(), _game.getTime());

    // _game.startTick(); // FOR GUI
    while (!_game.isGameOver()) {
        processInput();
    }
    // _game.stopTick();  // FOR GUI

    displayEnd();
    _game.Detach(this);
    std::this_thread::sleep_for(std::chrono::milliseconds(10000)); // 10sec
}

void Controller::displayEnd() {
    if (_game.getScore() >= _game.getMAX_SCORE() || _game.isTimeUp() ||
        _game.getTotalRowsCompleted() >= _game.getMAX_ROWSCOMPLETED()) {
        _view.displayWin();
    } else {
        _view.displayLost();
    }
}

void Controller::processInput() {
    std::string cmd = _view.askCommands();
    transform(cmd.begin(), cmd.end(), cmd.begin(), toupper);
    switch (cmd[0]) {
        case 'A':
            rotate(true);
            break;
        case 'E':
            rotate(false);
            break;
        case 'Q':
            move(Direction::LEFT);
            break;
        case 'D':
            move(Direction::RIGHT);
            break;
        case 'S':
            move(Direction::DOWN);
            break;
        case 'F':
            drop();
            break;
        case 'T':
            _game.setIsGameOver(true);
            break;
        default:
            _view.displayErrorCommands();
//            update();
    }
}


void Controller::drop() {
    _game.drop();
}

void Controller::move(const Direction2D &dir) {
    _game.move(dir);
}

void Controller::rotate(bool clockwise) {
    _game.rotate(clockwise);
}

void Controller::Update(const Subject *)  {
    clearConsole();
    _view.displayTitle();
    _view.displayBoard(_game);
    _view.displayLevelScore(_game.getLevel(), _game.getScore(), _game.getTotalRowsCompleted(), _game.getTime());
}


void Controller::clearConsole() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

