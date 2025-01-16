#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../metier/Game.h"
#include "../console/View.h"

/**
 * @brief The Controller class handles user input and game logic.
 *
 * This class is responsible for controlling the flow of the Tetris game,
 * interacting with the View class for user input and displaying game state,
 * and managing the game state through the Game class.
 */
class Controller: public Observer {

    Game _game; ///< The Game object representing the game state.
    View _view; ///< The View object responsible for displaying the game.

    /**
     * @brief Moves the current brick in the specified direction.
     *
     * @param dir The direction in which to move the Tetrimino.
     */
    void move(const Direction2D &dir);

    /**
     * @brief Rotates the current brick clockwise or counterclockwise.
     *
     * @param clockwise true to rotate the Tetrimino clockwise, false to rotate counterclockwise.
     */
    void rotate(bool clockwise);

    /**
     * @brief Drops the current brick down one step.
     *
     * This function drops the current Tetrimino down one step,
     * usually triggered by user input.
     */
    void drop();

    /**
     * @brief Clears the console screen.
     */
    void clearConsole();

    /**
     * @brief Processes user input and triggers corresponding actions.
     */
    void processInput();

    /**
     * @brief Displays the end message when the game is over.
     */
    void displayEnd();

    /**
     * @brief Updates the Controller.
     *
     * This function updates the Controller and view's state.
     */
    void Update(const Subject *) override;

public:
    /**
     * @brief Constructs a new Controller object.
     *
     * @param view The View object to be associated with the Controller.
     */
    Controller(View view);

    /**
     * @brief Starts the Tetris game loop.
     *
     * This function initializes the game state and enters a loop
     * where it continuously receives user input and updates the game state
     * until the game is over.
     */
    void start();

};

#endif // CONTROLLER_H
