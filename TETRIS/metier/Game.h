#ifndef GAME_H
#define GAME_H

#include "Subject.h"
#include "Board.h"
#include "Brick.h"
#include "Bag.h"
#include "Direction.h"
#include <thread>
#include <chrono>
#include <vector>
#include <atomic>
#include <functional>
#include <map>
/**
 * @brief The Game class represents the Tetris game logic.
 */
class Game : public Subject {
    static int constexpr MAX_TIME = 5; /// 5 minutes
    static int constexpr MAX_ROWSCOMPLETED = 210;
    static int constexpr MAX_SCORE = 50000;
    const std::map<int, double> LEVEL_SPEED ={
        {1,1000}, {2,883}, {3,816}, {4,750}, {5,683}, {6,616},
        {7,550}, {8,466}, {9,383}, {10, 300}, {11, 216}, {12, 133},
        {13,150}, {14, 133}, {15, 116}, {16, 100}, {17, 83}, {18, 66},
        {19, 50}, {20, 30}
    };

    Board _board;                     ///< Pointer to the game board.
    Bag _bag;                        ///< Pointer to the bag of bricks.
    Brick _currentBrick;            ///< Pointer to the current falling brick.
    Brick _nextBrick;
    int _score;                    ///< Current score of the game.
    int _level;                   ///< Current level of the game.
    long _speed;                 ///< Speed of the game.
    std::chrono::time_point<std::chrono::steady_clock> _time;
    int _totalRowsCompleted;
    bool _isGameOver;          ///< Flag indicating whether the game is over.
    int _brickCpt;
    std::atomic<bool> _isTickRunning; ///< Flag indicating whether the tick thread is running.
    std::thread _tickThread; ///< Thread for running the tick function.


    /**
     * @brief Deletes completed rows from the game board and returns the number of rows deleted.
     *
     * @param rowsCompleted The number of completed rows.
     * @return The number of rows deleted.
     */
    int deleteCompletedRows();

    /**
     * @brief Calculates the score increase based on the drop distance and initial positions of the current brick.
     *
     * @param initialPositions The initial positions of the current brick.
     * @return The calculated score increase.
     */
    int calculateDistanceDrop(const std::vector<Position> &initialPositions);

    /**
     * @brief Manages score and rules based on the drop distance.
     *
     * @param dropDistance The drop distance of the brick.
     */
    void manageScoreAndRules(int dropDistance);

    /**
     * @brief Sets the current falling brick.
     */
    void setCurrentBrick();

public:

    using UpdateCurrentThread = std::function<void()>; //will call back the function
    /**
     * @brief Constructs a new Game object with the specified board width and height.
     *
     * @param height The height of the game board.
     * @param width The width of the game board.
     */
    Game(int height = 20, int width = 10);
    /**
      * @brief Starts the tick thread for handling game events.
      */
    void startTick(const UpdateCurrentThread& updateCurrentThread);
    /**
     * @brief Stops the tick thread.
     */
    void stopTick();

    /**
     * @brief Moves the current falling brick in the specified direction.
     *
     * @param dir The direction in which to move the brick.
     */
    void move(const Direction2D &dir);

    /**
     * @brief Drops the current falling brick to the lowest possible position.
     */
    void drop();

    /**
     * @brief Rotates the current falling brick.
     *
     * @param clockwise Flag indicating whether to rotate the brick clockwise or counterclockwise.
     */
    void rotate(bool clockwise);

    /**
     * @brief Get the to string
     */
    std::string getTimeString() const;

    /**
     * @brief Get the time
     */
    std::chrono::time_point<std::chrono::steady_clock> getTime() const;

    /**
     * @brief Gets the current score of the game.
     *
     * @return The current score.
     */
    int getScore() const;

    /**
     * @brief Gets the current level of the game.
     *
     * @return The current level.
     */
    int getLevel() const;

    /**
     * @brief Gets the maximum score allowed in the game.
     *
     * @return The maximum score.
     */
    int getMAX_SCORE();

    /**
     * @brief Gets the maximum speed allowed in the game.
     *
     * @return The maximum speed.
     */
    int getMAX_TIME();

    /**
     * @brief Gets the maximum number of completed rows allowed in the game.
     *
     * @return The maximum number of completed rows.
     */
    int getMAX_ROWSCOMPLETED();

    /**
     * @brief Gets the current speed of the game.
     *
     * @return The current speed.
     */
    int getSpeed();

    /**
     * @brief Gets the next brick.
     *
     * @return The next brick.
     */
    Brick getNextBrick();

    /**
     * @brief Gets the game board.
     *
     * @return A pointer to the game board.
     */
    const Board &getBoardGame() const;

    /**
    * @brief Gets the bag of bricks.
    *
    * @return A constant reference to the bag of bricks.
    */
    const Bag &getBag() const;

    /**
     * @brief Gets the current falling brick.
     *
     * @return A pointer to the current falling brick.
     */
    const Brick &getCurrentBrick() const;


    /**
    * @brief Sets the game time to the specified value.
    *
    * @param time The time to set for the game.
    */
    void setTime(std::chrono::time_point<std::chrono::steady_clock> time);

    /**
     * @brief Sets the speed of the game.
     *
     * @param speed The speed of the game in seconds (e.g., 0.8s).
     */
    void setSpeed(long speed);

    /**
     * @brief Sets the game level.
     *
     * @param level The level to be set.
     */
    void setLevel(int level);

    /**
     * @brief Sets the game score.
     *
     * @param score The score to be set.
     */
    void setScore(int score);

    /**
     * @brief Sets the total number of rows completed.
     *
     * @param totalRowsCompleted The total number of rows completed.
     */
    void setTotalRowsCompleted(int totalRowsCompleted);

    /**
     * @brief Sets the game over flag.
     *
     * @param b True if the game is over, otherwise false.
     */
    void setIsGameOver(bool b);

    /**
    * @brief Starts the game timer.
    */
    void startTime();

    /**
    * @brief Checks if the game time is up.
    *
    * @return True if the time is up, otherwise false.
    */
    bool isTimeUp();

    /**
     * @brief Checks if the game is over.
     *
     * @return True if the game is over, otherwise false.
     */
    bool isGameOver();

    /**
     * @brief Checks game over rules and sets game over flag if necessary.
     */
    void checkGameOverRules();

    /**
     * @brief Adds score to the game based on the number of completed rows and drop distance.
     *
     * @param rowsCompleted The number of completed rows.
     * @param dropDistance The drop distance of the brick.
     */
    void addScore(int rowsCompleted, int dropDistance);

    /**
     * @brief Gets the total number of rows completed.
     *
     * @return The total number of rows completed.
     */
    int getTotalRowsCompleted() const;

    /**
     * @brief Fills the game board with bricks randomly according to the density.
     *
     * @param density The density of bricks to fill the board.
     */
    void fillBoardWithBricks(int density);
    /**
     * @brief Compute the speed of the game.
     */
    void computeSpeed();


    /**
     * @brief Assignment operator.
     *
     * This operator allows copying the attributes of one Game object into another.
     * It ensures a deep copy of pointer members.
     *
     * @param other The Game object from which to copy the attributes.
     * @return A reference to the modified Game object.
     */
    Game &operator=(const Game &other);
    void Attach(Observer* observer) override;
    void Detach(Observer* observer) override;
    void Notify() const override;

};

#endif // GAME_H
