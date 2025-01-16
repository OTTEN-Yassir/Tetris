#include "gameoptions.h"
#include "gameboard.h"
#include "ui_gameoptions.h"

GameOptions::GameOptions(QWidget *parent)
    : QMainWindow(parent)
    , _ui(new Ui::GameOptions)
{
    _ui->setupUi(this);
    setWindowTitle("OPTIONS TETRIS");
    QPushButton* launchButton = _ui->launchButton;
    connect(launchButton, &QPushButton::clicked, [this]() { launchGame(); });
}

void GameOptions::launchGame(){
    int height = _ui->HeightSpinBox->value();
    int width = _ui->WidthSpinBox->value();
    int level = _ui->levelSpinBox->value();
    int preFilled = _ui->preFilledSpinBox->value();

    //create The Game and the GameBoard with the goods values
    _gameboard = std::make_shared<GameBoard>(height, width, level, preFilled);
    this->close();
    _gameboard->show();
}

GameOptions::~GameOptions(){
    delete _ui;
}