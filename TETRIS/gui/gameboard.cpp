#include "gameboard.h"
#include "ui_gameboard.h"
#include <qtimer.h>

GameBoard::GameBoard(int height, int width, int level, int preFilled,
                     QWidget *parent)
    : QMainWindow(parent), _ui(new Ui::GameBoard), _height(height),
    _width(width), _cptColor(0) {
    _game = Game(_height, _width);
    _ui->setupUi(this);
    _game.setLevel(level);

    if (preFilled != 0) {
        _game.fillBoardWithBricks(preFilled);
    }

    setWindowTitle("TETRIS");
    _ui->BoardTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    _ui->BoardTableWidget->setSelectionMode(QAbstractItemView::NoSelection);
    _ui->BoardTableWidget->verticalHeader()->setVisible(false);
    _ui->BoardTableWidget->horizontalHeader()->setVisible(false);
    _ui->nextBrick->setEditTriggers(QAbstractItemView::NoEditTriggers);
    _ui->nextBrick->setSelectionMode(QAbstractItemView::NoSelection);
    _ui->nextBrick->verticalHeader()->setVisible(false);
    _ui->nextBrick->horizontalHeader()->setVisible(false);

    createMenu();
    createColoredSquares();
    getNextBrick();

    _game.Attach(this);
    _game.startTime();

    connect(this, &GameBoard::HaveToMoveDown, this,
            &GameBoard::moveBrickDown);
    startTick();
}

void GameBoard::createMenu() {
    QMenu *gameMenu = menuBar()->addMenu(tr("Menu"));
    QAction *newGameAction = new QAction(tr("New Game"), this);
    connect(newGameAction, &QAction::triggered, this, &GameBoard::newGame);
    gameMenu->addAction(newGameAction);

    QAction *exitAction = new QAction(tr("Exit"), this);
    connect(exitAction, &QAction::triggered, this, &GameBoard::quitGame);
    gameMenu->addAction(exitAction);
}

void GameBoard::newGame() {
    _gameOptions = std::make_shared<GameOptions>();
    stopTick();
    this->close();
    _gameOptions->show();
}

void GameBoard::quitGame() {
    stopTick();
    this->close();
}

void GameBoard::createColoredSquares() {
    _ui->BoardTableWidget->clearContents();
    _ui->BoardTableWidget->setRowCount(_height);
    _ui->BoardTableWidget->setColumnCount(_width);

    float cellFraction = 0.1;
    int squareSize = qMin(_ui->BoardTableWidget->width(), _ui->BoardTableWidget->height()) *
                     cellFraction; // TODO: maybe fix the size

    int widgetWidth = (_width * squareSize + 1);
    int widgetHeight = (_height * squareSize + 1);

    _ui->BoardTableWidget->setMinimumSize(widgetWidth, widgetHeight);

    for (int row = 0; row < _height; ++row) {
        _ui->BoardTableWidget->setRowHeight(row, squareSize);
        for (int col = 0; col < _width; ++col) {
            _ui->BoardTableWidget->setColumnWidth(col, squareSize);
            QTableWidgetItem *item = new QTableWidgetItem();
            if (!_game.getBoardGame().getBoard().at(row).at(col)->getIsOccupied()) {
                item->setBackground(Qt::white);
            }
            _ui->BoardTableWidget->setItem(row, col, item);
        }
    }

    for (const auto &e : _game.getCurrentBrick().getVecPos()) {
        QTableWidgetItem *item = new QTableWidgetItem();
        item->setBackground(Qt::darkCyan);
        _ui->BoardTableWidget->setItem(e.getX(), e.getY(), item);
    }
}

void GameBoard::getNextBrick() {
    _ui->nextBrick->clearContents();
    _ui->nextBrick->setRowCount(5);
    _ui->nextBrick->setColumnCount(5);

    const auto vec = _game.getNextBrick().getVecPos();
    for (int row = 0; row < 5; ++row) {
        _ui->nextBrick->setRowHeight(row, 40);
        for (int col = 0; col < 5; ++col) {
            _ui->nextBrick->setColumnWidth(col, 20);
            QTableWidgetItem *item = new QTableWidgetItem();
            item->setBackground(Qt::white);

            _ui->nextBrick->setItem(row, col, item);
        }
    }

    for (const auto &e : vec) {
        QTableWidgetItem *item = new QTableWidgetItem();
        item->setBackground(Qt::darkCyan);
        int row = e.getX() + 1;
        int col = e.getY() + 2;

        _ui->nextBrick->setItem(row, col, item);
    }
}

void GameBoard::keyPressEvent(QKeyEvent *event) {
    if (event->key() == 0x51 || event->key() == Qt::Key_Q) { // 0x51 Qt::Key_Q
        _game.move(Direction::LEFT);
    } else if (event->key() == 0x53 ||
               event->key() == Qt::Key_S) {
        _game.move(Direction::DOWN);
    } else if (event->key() == 0x44 ||
               event->key() == Qt::Key_D ) {
        _game.move(Direction::RIGHT);
    } else if (event->key() == 0x41 ||
               event->key() == Qt::Key_A) {
        _game.rotate(false);
    } else if (event->key() == 0x45 || event->key() == Qt::Key_E) {
        _game.rotate(true);
    } else if (event->key() == 0x46 || event->key() == Qt::Key_F) {
        _game.drop();
    }
}

void GameBoard::moveBrickDown() { _game.move(Direction::DOWN); }

void GameBoard::startTick() {
    _game.startTick([this]() {
        emit HaveToMoveDown();
    });
}

void GameBoard::stopTick() { _game.stopTick(); }

void GameBoard::Update(const Subject *) {
    if(!_game.isGameOver()){
        displayInformations(_game.getScore(), _game.getLevel(),
                            _game.getTotalRowsCompleted(), _game.getTimeString());
        displayBoard();
        getNextBrick();
    }else{
        disconnect(this, &GameBoard::HaveToMoveDown, this, &GameBoard::moveBrickDown);//disconnect the signal sent by the tick
        displayGameOver();
        this->close();
    }
}
void GameBoard::displayInformations(int score, int level, int rows,
                                    std::string time) {
    // change the values to display
    _ui->ScoreTextEdit->setText(QString::number(score));
    _ui->LevelTextEdit->setText(QString::number(level));
    _ui->RowsTextEdit->setText(QString::number(rows));
    _ui->timer->setText(QString::fromStdString(time));
}
void GameBoard::displayBoard() {
    for (int row = 0; row < _height; ++row) {
        for (int col = 0; col < _width; ++col) {
            QTableWidgetItem *item = new QTableWidgetItem();
            if (!_game.getBoardGame().getBoard().at(row).at(col)->getIsOccupied()) {
                item->setBackground(Qt::white);
            } else {
                item->setBackground(Qt::darkCyan);
            }
            _ui->BoardTableWidget->setItem(row, col, item);
        }
    }

    for (const auto &e : _game.getCurrentBrick().getVecPos()) {
        QTableWidgetItem *item = new QTableWidgetItem();
        item->setBackground(Qt::darkCyan);
        _ui->BoardTableWidget->setItem(e.getX(), e.getY(), item);
    }
}
void GameBoard::displayGameOver() {
    stopTick();
    QMessageBox messageBox;
    messageBox.setWindowTitle("End Game");
    messageBox.setText("The Game is over !");
    messageBox.setInformativeText("New Game or Quit?");
    messageBox.addButton("New Game", QMessageBox::AcceptRole);
    messageBox.addButton("Quit", QMessageBox::RejectRole);
    messageBox.setDefaultButton(QMessageBox::Close);

    int choice = messageBox.exec();
    if (choice == QMessageBox::AcceptRole) {
        newGame();
    } else if (choice == QMessageBox::RejectRole) {
        quitGame();
    }
}
GameBoard::~GameBoard() {
    _game.Detach(this);
    delete _ui;
    delete _timer;
}
