#ifndef BOARD_H
#define BOARD_H

#include "Square.h"
#include <memory>
#include "Direction.h"
#include "Brick.h"

/**
 * @brief The Board class represents the game board in a Tetris game.
 */
class Board {
    bool _isGameOver; ///< Flag indicating whether the game is over.
    int _height;     ///< The height of the board.
    int _width;     ///< The width of the board.
    std::vector<std::vector<std::unique_ptr<Square>>> _board; ///< 2D vector representing the board.

    /**
     * @brief Checks if moving the current brick in the specified direction is valid.
     *
     * @param currentBrick The current brick to be moved.
     * @param dir The direction in which to move the brick.
     * @return True if the move is valid, otherwise false.
     */
    bool checkMove(Brick &currentBrick, const Direction2D &dir);

    /**
     * @brief Places the current brick onto the board.
     *
     * @param currentBrick The current brick to be placed.
     */
    void placeBrick(const Brick &currentBrick);

    /**
     * @brief Picks the current brick from the board.
     *
     * @param currentBrick The current brick to be picked.
     */
    void pickBrick(const Brick &currentBrick);

    /**
     * @brief Checks if rotating the current brick is valid.
     *
     * @param currentBrick The current brick to be rotated.
     * @param tmp A temporary brick used for rotation.
     * @return True if the rotation is valid, otherwise false.
     */
    bool checkRotating(Brick &currentBrick, Brick &tmp);

public:
    /**
     * @brief Constructor for the Board class with custom width and height.
     *
     * @param height The height of the board.
     * @param width The width of the board.
     */
    Board(int height = 20, int width = 10);


    /**
    * @brief Adds a brick to the board.
    *
    * @param currentBrick The brick to add.
    */
    void addBrick(Brick &currentBrick);

    /**
     * @brief Moves the current brick in the specified direction.
     *
     * @param currentBrick The current brick to be moved.
     * @param dir The direction in which to move the brick.
     * @return True if the current brick can move down, otherwise false.
     */
    bool move(Brick &currentBrick, const Direction2D &dir);

    /**
     * @brief Rotates the current brick.
     *
     * @param currentBrick The current brick to be rotated.
     * @param clockwise Flag indicating whether to rotate the brick clockwise or counterclockwise.
     * @return True if the rotation is successful, otherwise false.
     */
    bool rotateBrick(Brick &currentBrick, bool clockwise);

    /**
     * @brief Checks if a row is completed.
     *
     * @param row The row to check.
     * @return True if the row is completed, otherwise false.
     */
    bool isCompletedRow(int row);

    /**
     * @brief Deletes a completed row.
     *
     * @param row The row to delete.
     */
    void deleteRow(int row);

    /**
     * @brief Drops rows above the deleted row.
     *
     * @param maxRows The maximum number of rows to drop.
     */
    void dropRows(int maxRows);

    /**
     * @brief Checks if moving the current brick to the specified position is valid.
     *
     * @param newPos The new position to move the brick to.
     * @return True if the move is valid, otherwise false.
     */
    bool isValidMove(const Position &newPos) const;

    /**
     * @brief Getter for the height of the board.
     *
     * @return The height of the board.
     */
    int getHeight() const;

    /**
     * @brief Getter for the width of the board.
     *
     * @return The width of the board.
     */
    int getWidth() const;

    /**
     * @brief Getter for the board.
     *
     * @return A constant reference to the board.
     */
    const std::vector<std::vector<std::unique_ptr<Square>>> &getBoard() const;

    /**
     * @brief Checks if the game is over.
     *
     * @return True if the game is over, otherwise false.
     */
    bool isGameOver() const;

    /**
     * @brief Sets the game over flag.
     *
     * @param isGameOver True if the game is over, otherwise false.
     */
    void setIsGameOver(bool isGameOver);

    /**
     * @brief Assignment operator.
     *
     * @param other The Board object from which to copy the attributes.
     * @return A reference to the modified Board object.
     */
    Board &operator=(const Board &other);
};

#endif // BOARD_H
