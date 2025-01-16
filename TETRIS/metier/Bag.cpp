#include "Bag.h"
#include <algorithm>
#include <random>
#include "DefaultBricks.h"

Bag::Bag() {
    _bricks.push_back(DefaultBricks::BRICKSQUARE);
    _bricks.push_back(DefaultBricks::BRICKS);
    _bricks.push_back(DefaultBricks::BRICKI);
    _bricks.push_back(DefaultBricks::BRICKJ);
    _bricks.push_back(DefaultBricks::BRICKL);
    _bricks.push_back(DefaultBricks::BRICKT);
    _bricks.push_back(DefaultBricks::BRICKZ);
}

void Bag::shuffle() {
    std::random_device rd;
    std::default_random_engine rng(rd());
    std::shuffle(_bricks.begin(), _bricks.end(), rng);
}

const std::vector<Brick>& Bag::getBricks() const {
    return _bricks;
}
