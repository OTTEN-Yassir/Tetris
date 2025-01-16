#ifndef SQUARE_H
#define SQUARE_H

/**
 * @brief The Square class represents a single square in the Tetris game board.
 */
class Square {
    bool _isOccupied; ///< Flag indicating whether the square is occupied.
public:
    /**
     * @brief Constructs a Square object with the specified occupancy.
     *
     * @param isOccupied Flag indicating whether the square is occupied.
     */
    Square(bool isOccupied);

    /**
     * @brief Checks if the square is occupied.
     *
     * @return True if the square is occupied, false otherwise.
     */
    bool getIsOccupied() const;

    /**
     * @brief Sets the occupancy status of the square.
     *
     * @param isOccupied Flag indicating whether the square is occupied.
     */
    void setIsOccupied(bool isOccupied);
};

#endif // SQUARE_H
