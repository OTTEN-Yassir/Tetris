#ifndef DEFAULTBRICKS_H
#define DEFAULTBRICKS_H

#include "Brick.h"

/**
 * @brief The DefaultBricks class represents a factory for generating Tetris bricks.
 *
 * This struct provides static members representing different Tetris bricks that can be generated.
 * Each static member holds a constant Brick object representing a specific Tetris brick shape.
 */
struct DefaultBricks {
    static const Brick BRICKSQUARE;
    static const Brick BRICKL;
    static const Brick BRICKS;
    static const Brick BRICKI;
    static const Brick BRICKT;
    static const Brick BRICKJ;
    static const Brick BRICKZ;
};

#endif // DEFAULTBRICKS_H
