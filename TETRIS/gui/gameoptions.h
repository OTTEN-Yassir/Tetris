#ifndef GAMEOPTIONS_H
#define GAMEOPTIONS_H


#include <QMainWindow>

class GameBoard;

namespace Ui {
class GameOptions;
}

class GameOptions : public QMainWindow {
    Q_OBJECT

public:
    /**
   * @brief Constructor for the GameOptions class.
   * @param parent The parent widget.
   */
    explicit GameOptions(QWidget *parent = nullptr);
    /**
   * @brief Destructor for the GameOptions class.
   */
    ~GameOptions();
    /**
   * @brief Launches the game.
   */
    void launchGame();

private:
    Ui::GameOptions* _ui;
    std::shared_ptr<GameBoard> _gameboard;
};

#endif // GAMEOPTIONS_H
