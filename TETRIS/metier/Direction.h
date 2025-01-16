#ifndef DIRECTION_H
#define DIRECTION_H

#include <utility>

using Direction2D = std::pair<int, int>;

/**
 * @brief The Direction struct
 */
struct Direction {
    static const Direction2D LEFT;
    static const Direction2D RIGHT;
    static const Direction2D DOWN;
};

#endif // DIRECTION_H
