#ifndef POSITION_H
#define POSITION_H

#include <ostream>
#include <utility>
#include "Direction.h"

/**
 * @brief The Position class represents a position on a 2D grid.
 */
class Position {
    std::pair<int, int> _pos;

public:
    /**
     * @brief Default constructor for Position.
     *
     * Initializes the position to (0, 0).
     */
    Position() = default;

    /**
     * @brief Constructs a Position object with the specified coordinates.
     *
     * @param x The x-coordinate of the position.
     * @param y The y-coordinate of the position.
     */
    Position(int x, int y);

    /**
     * @brief Gets the x-coordinate of the position.
     *
     * @return The x-coordinate of the position.
     */
    int getX() const;

    /**
     * @brief Gets the y-coordinate of the position.
     *
     * @return The y-coordinate of the position.
     */
    int getY() const;

    /**
     * @brief Sets the x-coordinate of the position.
     *
     * @param x The new value for the x-coordinate.
     */
    void setX(int x);

    /**
     * @brief Sets the y-coordinate of the position.
     *
     * @param y The new value for the y-coordinate.
     */
    void setY(int y);

    /**
     * @brief Overloaded equality operator.
     *
     * @param other The Position object to compare with.
     * @return True if the positions are equal, false otherwise.
     */
    bool operator==(const Position &other) const;

    /**
     * @brief Assignment operator.
     *
     * @param other The Position object from which to copy the attributes.
     * @return A reference to the modified Position object.
     */
    Position &operator=(const Position &other);
};

/**
 * @brief Overloaded stream insertion operator to output a Position object.
 *
 * @param os The output stream.
 * @param pos The Position object to output.
 * @return The output stream after the position has been written to it.
 */
std::ostream &operator<<(std::ostream &os, const Position &pos);

/**
 * @brief Overloaded addition operator to add a direction to a position.
 *
 * @param dir The direction to add.
 * @param p The position to add the direction to.
 * @return The resulting position after adding the direction.
 */
Position operator+(const Direction2D &dir, const Position &p);

/**
 * @brief Overloaded addition operator to add a position to a direction.
 *
 * @param p The position to add the direction to.
 * @param dir The direction to add.
 * @return The resulting position after adding the direction.
 */
Position operator+(const Position &p, const Direction2D &dir);

/**
 * @brief Overloaded subtraction operator to subtract one position from another.
 *
 * @param p1 The minuend position.
 * @param p2 The subtrahend position.
 * @return The resulting position after subtracting p2 from p1.
 */
Position operator-(const Position &p1, const Position &p2);

#endif // POSITION_H
