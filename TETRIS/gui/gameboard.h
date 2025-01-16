#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "../metier/Game.h"
#include "gameoptions.h"
#include <QMainWindow>
#include <QTextEdit>
#include <QTableWidget>
#include <QKeyEvent>
#include <QThread>
#include <QMessageBox>

namespace Ui {
class GameBoard;
}

class GameBoard : public QMainWindow, public Observer
{
    Q_OBJECT

public:
    /**
   * @brief Constructor for the GameBoard class.
   * @param height The height of the game board.
   * @param width The width of the game board.
   * @param level The starting level of the game.
   * @param preFilled The number of pre-filled rows on the game board.
   * @param parent The parent widget.
   */
    explicit GameBoard(int height, int width, int level, int preFilled,
                       QWidget *parent = nullptr);
    /**
   * @brief Destructor for the GameBoard class.
   */
    ~GameBoard();
    /**
   * @brief Creates colored squares for the game board.
   */
    void createColoredSquares();
    /**
   * @brief Gets the next brick for display.
   */
    void getNextBrick();
    /**
   * @brief Creates the menu for the game.
   */
    void createMenu();
    /**
   * @brief Displays game information such as score, level, rows, and time.
   * @param score The current score.
   * @param level The current level.
   * @param rows The total rows completed.
   * @param time The elapsed time.
   */
    void displayInformations(int score, int level, int rows, std::string time);
    /**
   * @brief Displays the game board.
   */
    void displayBoard();

    /**
   * @brief Starts the tick for the game.
   */
    void startTick();
    /**
   * @brief Stops the tick for the game.
   */
    void stopTick();
    /**
   * @brief Moves the brick down.
   */
    void moveBrickDown();
    /**
   * @brief Displays the game over message.
   */
    void displayGameOver();

protected:
    /**
   * @brief Overridden function to handle update from the observer.
   * @param subject The subject that triggered the update.
   */
    void Update(const Subject *) override;
    /**
   * @brief Overridden function to handle key press events.
   * @param event The key event.
   */
    void keyPressEvent(QKeyEvent *event) override;
private slots:
    /**
   * @brief Slot function to start a new game.
   */
    void newGame();
    /**
   * @brief Slot function to quit the game.
   */
    void quitGame();
signals:
    /**
   * @brief Signal emitted when a move down action is required.
   */
    void HaveToMoveDown();

private:
    QTimer* _timer;
    Ui::GameBoard* _ui;
    int _height;
    int _width;
    int _cptColor;
    Game _game;
    std::shared_ptr<GameOptions> _gameOptions ;
};

#endif // GAMEBOARD_H
