#include "DefaultBricks.h"

const Brick DefaultBricks::BRICKSQUARE = Brick(Position(0, 0), {{0, 0},
                                                                {0, 1},
                                                                {1, 0},
                                                                {1, 1}});
const Brick DefaultBricks::BRICKL = Brick(Position(1, 0), {{1, 0},
                                                           {0, 0},
                                                           {2, 0},
                                                           {2, 1}});
const Brick DefaultBricks::BRICKS = Brick(Position(0, 0), {{0, 0},
                                                           {1, -1},
                                                           {1, 0},
                                                           {0, 1}});
const Brick DefaultBricks::BRICKI = Brick(Position(1, 0), {{1, 0},
                                                           {0, 0},
                                                           {2, 0},
                                                           {3, 0}});
const Brick DefaultBricks::BRICKT = Brick(Position(0, 0), {{0, 0},
                                                           {0, -1},
                                                           {1, 0},
                                                           {0, 1}});
const Brick DefaultBricks::BRICKJ = Brick(Position(1, 0), {{1, 0},
                                                           {0, 0},
                                                           {2, 0},
                                                           {2, -1}});
const Brick DefaultBricks::BRICKZ = Brick(Position(0, 0), {{0, 0},
                                                           {0, -1},
                                                           {1, 0},
                                                           {1, 1}});
