#ifndef VIEW_H
#define VIEW_H

#include "../metier/Game.h"

/**
 * @brief The View class represents the Tetris game view.
 *
 * This class is responsible for displaying the Tetris game and interacting with the user.
 */
class View {
public:
    /**
     * @brief Default constructor for the View class.
     */
    View() = default;

    /**
     * @brief Displays the Tetris game title.
     */
    void displayTitle();

    /**
     * @brief Displays the game board.
     *
     * @param game A const reference to the Game object containing information about the game board.
     */
    void displayBoard(const Game &game);

    /**
     * @brief Displays the current level, score, and completed rows of the player.
     *
     * @param level The current level of the player.
     * @param score The current score of the player.
     * @param completedRows The number of completed rows.
     */
    void displayLevelScore(int level, int score, int completedRows,
                           std::chrono::time_point<std::chrono::steady_clock> startTime);

    /**
     * @brief Asks the user to enter a command.
     *
     * @return A string representing the command entered by the user.
     */
    std::string askCommands();

    /**
     * @brief Asks the user if they want to modify the size of the game board.
     *
     * @return true if the user wants to modify the size of the board, false otherwise.
     */
    bool wantUpdateSize();

    /**
     * @brief Asks the user for the desired size of the game board.
     *
     * @return A pair of integers representing the desired height and width of the game board.
     */
    std::pair<int, int> askSize();

    /**
     * @brief Displays an error message for an invalid command.
     */
    void displayErrorCommands();

    /**
     * @brief Displays a message indicating that the player has lost the game.
     */
    void displayLost();

    /**
     * @brief Displays a message indicating that the player has won the game.
     */
    void displayWin();

    /**
     * @brief Asks the user if they want to pre-fill the game board with bricks.
     *
     * @return true if the user wants to pre-fill the board, false otherwise.
     */
    bool wantPreFillBoard();

    /**
     * @brief Asks the user for the desired density of pre-filled bricks on the game board.
     *
     * @return An integer representing the desired density of bricks.
     */
    int askDensity();

    /**
     * @brief Asks the user for the desired game level.
     *
     * @return An integer representing the desired game level.
     */
    int askLevel();

    /**
     * @brief Asks the user if they want to change the game level.
     *
     * @return true if the user wants to change the level, false otherwise.
     */
    bool wantChangeLevel();

    /**
     * @brief Clears the input stream.
     */
    void clearCin() const;

    /**
     * @brief Displays the elapsed time of the game.
     *
     * @param startTime The start time of the game.
     */
    void displayTime(std::chrono::time_point<std::chrono::steady_clock> startTime);

};

#endif // VIEW_H
