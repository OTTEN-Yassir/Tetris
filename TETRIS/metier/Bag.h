#ifndef BAG_H
#define BAG_H

#include "Brick.h"
#include <vector>


/**
 * @brief The Bag class represents a bag containing Tetris bricks.
 */
class Bag {
    std::vector<Brick> _bricks;
public:
    /**
     * @brief Constructs a Bag object.
     *
     * The constructor initializes an empty bag.
     */
    Bag();

    /**
     * @brief Shuffles the bricks in the bag.
     *
     * This method shuffles the order of bricks in the bag randomly.
     */
    void shuffle();

    /**
     * @brief Gets the bricks in the bag.
     *
     * @return A constant reference to the vector of bricks in the bag.
     */
    const std::vector<Brick>& getBricks() const;
};

#endif // BAG_H
