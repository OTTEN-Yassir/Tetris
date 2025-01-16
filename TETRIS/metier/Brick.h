#ifndef BRICK_H
#define BRICK_H

#include "Position.h"
#include "Direction.h"
#include <vector>

/**
 * @brief The Brick class represents a brick in the Tetris game.
 *
 * This class encapsulates the properties and behaviors of a brick in the Tetris game.
 */
class Brick {
    Position                _center;     ///< Center position of the brick.
    std::vector<Position>   _vecPos;    ///< Vector of positions representing the squares composing the brick.

public:

    /**
     * @brief Default constructor.
     * Constructs an empty Brick object.
     */
    Brick() = default;

    /**
     * @brief Constructs a Brick object with the specified center position and vector of positions.
     *
     * @param center The center position of the brick.
     * @param vecPos Vector containing the positions of squares composing the brick.
     */
    Brick(const Position& center, const std::vector<Position>& vecPos);

    /**
     * @brief Rotates the brick.
     *
     * @param clockwise Flag indicating whether to rotate the brick clockwise or counterclockwise.
     * Rotates the brick by 90 degrees in the specified direction.
     */
    void rotate(bool clockwise);

    /**
     * @brief Moves the brick in the specified direction.
     *
     * @param dir The direction in which to move the brick.
     */
    void move(const Direction2D & dir);

    /**
     * @brief Gets the vector of positions of the brick.
     *
     * @return A vector of positions representing the squares composing the brick.
     */
    std::vector<Position> getVecPos() const;

    /**
     * @brief Gets the center position of the brick.
     *
     * @return The center position of the brick.
     */
    const Position& getCenter() const;

    /**
     * @brief Sets the center position of the brick.
     *
     * @param pos The new center position of the brick.
     */
    void setCenter(const Position& pos);

    /**
     * @brief Sets the vector of positions of the brick.
     *
     * @param vecPos The new vector of positions representing the squares composing the brick.
     */
    void setVecPos(const std::vector<Position>& vecPos);

    /**
     * @brief Overloaded equality operator.
     *
     * @param other The brick to compare with.
     * @return True if the bricks are equal, false otherwise.
     */
    bool operator==(const Brick& other) const;

    /**
     * @brief Overloaded assignment operator.
     *
     * @param other The brick to copy.
     * @return Reference to the copied brick.
     */
    Brick& operator=(const Brick& other);
};

#endif // BRICK_H
