#include <catch2/catch_test_macros.hpp>
#include "Position.h"
#include "Brick.h"
#include "DefaultBricks.h"
#include "Board.h"
#include "Bag.h"
#include "../Console/Controller.h"
#include <iostream>


// In option for execute the tests : -s --colour-mode ansi

TEST_CASE("Position.cpp") {
    SECTION("Build a Postion") {
        auto p1 = Position(1, 2);
        REQUIRE(p1.getX() == 1);
        REQUIRE(p1.getY() == 2);
    }

    SECTION("Operator+ and Direction") {
        auto p1 = Position(1, 2);
        Direction2D dir = Direction::LEFT;
        p1 = p1 + dir;
        REQUIRE(p1.getX() == 1);
        REQUIRE(p1.getY() == 1);
    }

    SECTION("Direction and Operator+") {
        auto p1 = Position(1, 2);
        Direction2D dir = Direction::LEFT;
        p1 = dir + p1;
        REQUIRE(p1.getX() == 1);
        REQUIRE(p1.getY() == 1);
    }

    SECTION("Operator- and Direction") {
        auto p1 = Position(1, 2);
        auto p2 = Position(5, 8);
        auto result = p1 - p2;
        REQUIRE(result.getX() == (-4));
        REQUIRE(result.getY() == (-6));
    }
}

TEST_CASE("Brick.cpp") {

    SECTION("rotateBrick -> SQUARE") {
        Brick brick = DefaultBricks::BRICKSQUARE;

        brick.rotate(false);
        auto rotatedPositions = brick.getVecPos();

        REQUIRE(rotatedPositions[0] == Position(0, 0));
        REQUIRE(rotatedPositions[1] == Position(-1, 0));
        REQUIRE(rotatedPositions[2] == Position(0, 1));
        REQUIRE(rotatedPositions[3] == Position(-1, 1));
    }

    SECTION("rotateBrick -> I") {
        Brick brick = DefaultBricks::BRICKI;

        brick.rotate(false);
        auto rotatedPositions = brick.getVecPos();

        REQUIRE(rotatedPositions[0] == Position(1, 0));
        REQUIRE(rotatedPositions[1] == Position(1, -1));
        REQUIRE(rotatedPositions[2] == Position(1, 1));
        REQUIRE(rotatedPositions[3] == Position(1, 2));
    }

    SECTION("rotateBrick -> L") {
        Brick brick = DefaultBricks::BRICKL;

        brick.rotate(false);
        auto rotatedPositions = brick.getVecPos();

        REQUIRE(rotatedPositions[0] == Position(1, 0));
        REQUIRE(rotatedPositions[1] == Position(1, -1));
        REQUIRE(rotatedPositions[2] == Position(1, 1));
        REQUIRE(rotatedPositions[3] == Position(0, 1));
    }

    SECTION("rotateBrick -> S") {
        Brick brick = DefaultBricks::BRICKS;

        brick.rotate(false);
        auto rotatedPositions = brick.getVecPos();

        REQUIRE(rotatedPositions[0] == Position(0, 0));
        REQUIRE(rotatedPositions[1] == Position(1, 1));
        REQUIRE(rotatedPositions[2] == Position(0, 1));
        REQUIRE(rotatedPositions[3] == Position(-1, 0));
    }

    SECTION("rotateBrick -> T") {
        Brick brick = DefaultBricks::BRICKT;

        brick.rotate(false);
        auto rotatedPositions = brick.getVecPos();

        REQUIRE(rotatedPositions[0] == Position(0, 0));
        REQUIRE(rotatedPositions[1] == Position(1, 0));
        REQUIRE(rotatedPositions[2] == Position(0, 1));
        REQUIRE(rotatedPositions[3] == Position(-1, 0));
    }

    SECTION("rotateBrick -> J") {
        Brick brick = DefaultBricks::BRICKJ;

        brick.rotate(false);
        auto rotatedPositions = brick.getVecPos();

        REQUIRE(rotatedPositions[0] == Position(1, 0));
        REQUIRE(rotatedPositions[1] == Position(1, -1));
        REQUIRE(rotatedPositions[2] == Position(1, 1));
        REQUIRE(rotatedPositions[3] == Position(2, 1));
    }

    SECTION("rotateBrick -> Z") {
        Brick brick = DefaultBricks::BRICKZ;

        brick.rotate(false);
        auto rotatedPositions = brick.getVecPos();

        REQUIRE(rotatedPositions[0] == Position(0, 0));
        REQUIRE(rotatedPositions[1] == Position(1, 0));
        REQUIRE(rotatedPositions[2] == Position(0, 1));
        REQUIRE(rotatedPositions[3] == Position(-1, 1));
    }

    SECTION("moveBrick -> RIGHT") {
        Brick brick = DefaultBricks::BRICKI;

        brick.move(Direction::RIGHT);
        auto movedPositions = brick.getVecPos();

        REQUIRE(movedPositions[0] == Position(1, 1));
        REQUIRE(movedPositions[1] == Position(0, 1));
        REQUIRE(movedPositions[2] == Position(2, 1));
        REQUIRE(movedPositions[3] == Position(3, 1));
    }

    SECTION("moveBrick -> LEFT") {
        Brick brick = DefaultBricks::BRICKI;

        brick.move(Direction::LEFT);
        auto movedPositions = brick.getVecPos();

        REQUIRE(movedPositions[0] == Position(1, -1));
        REQUIRE(movedPositions[1] == Position(0, -1));
        REQUIRE(movedPositions[2] == Position(2, -1));
        REQUIRE(movedPositions[3] == Position(3, -1));
    }

    SECTION("moveBrick -> DOWN") {
        Brick brick = DefaultBricks::BRICKI;

        brick.move(Direction::DOWN);
        auto movedPositions = brick.getVecPos();

        REQUIRE(movedPositions[0] == Position(2, 0));
        REQUIRE(movedPositions[1] == Position(1, 0));
        REQUIRE(movedPositions[2] == Position(3, 0));
        REQUIRE(movedPositions[3] == Position(4, 0));
    }
}

TEST_CASE("Board.cpp") {
    SECTION("Create a baord with default values") {
        Board board = Board();
        REQUIRE(board.getHeight() == (20));
        REQUIRE(board.getWidth() == (10));
    }SECTION("Create a baord with specific values") {
        Board board = Board(30, 50);
        REQUIRE(board.getHeight() == (30));
        REQUIRE(board.getWidth() == (50));
    }SECTION("isValideMove with position out of board") {
        Board board = Board(30, 50);
        Position out = Position(500, 500);
        REQUIRE(board.isValidMove(out) == (false));
    }SECTION("isValideMove with good position in the board") {
        Board board = Board(30, 50);
        Position out = Position(10, 10);
        REQUIRE(board.isValidMove(out) == (true));
    }SECTION("move") {
        Board board;
        Brick brick(DefaultBricks::BRICKL);
        board.addBrick(brick);
        for (int i = 0; i < 10; ++i) {
            board.move(brick, Direction::DOWN);
        }
        REQUIRE(brick.getCenter().getX() == 11);
        REQUIRE(brick.getCenter().getY() == 4);
    }SECTION("rotate") {
        Board board;
        Brick brick(DefaultBricks::BRICKL);
        board.addBrick(brick);
        board.move(brick, Direction::DOWN);
        board.move(brick, Direction::DOWN);
        board.rotateBrick(brick, false);
    }SECTION("rotate T") {
        Board board;
        Brick brick(DefaultBricks::BRICKI);
        board.addBrick(brick);
        board.move(brick, Direction::RIGHT);
        board.move(brick, Direction::RIGHT);
        board.move(brick, Direction::RIGHT);
        board.move(brick, Direction::RIGHT);
        board.move(brick, Direction::RIGHT);
        board.move(brick, Direction::RIGHT);
        board.move(brick, Direction::RIGHT);
        board.rotateBrick(brick, false);
    }
}


TEST_CASE("Bag.cpp") {
    SECTION("Create a bag and its vectors") {
        Bag bag;
        REQUIRE(bag.getBricks().size() == (7));
    }SECTION("Create a bag and its vectors") {
        Bag bag;
        std::vector<Brick> bricks;
        bricks.push_back(DefaultBricks::BRICKSQUARE);
        bricks.push_back(DefaultBricks::BRICKS);
        bricks.push_back(DefaultBricks::BRICKI);
        bricks.push_back(DefaultBricks::BRICKJ);
        bricks.push_back(DefaultBricks::BRICKL);
        bricks.push_back(DefaultBricks::BRICKT);
        bricks.push_back(DefaultBricks::BRICKZ);
        REQUIRE(bag.getBricks() == bricks);
        bag.shuffle();
        REQUIRE(bag.getBricks() != bricks);
    }

}

TEST_CASE("Game.cpp") {
    SECTION("Create a game and its components") {
        Game game(20, 10);
        REQUIRE(game.getBag().getBricks().size() == 7);
        REQUIRE(game.getCurrentBrick().getVecPos().size() == 4);
    }
    SECTION("Game ends when total rows completed exceeds max rows completed") {
        Game game;

        game.setTotalRowsCompleted(game.getMAX_ROWSCOMPLETED() + 1);
        game.checkGameOverRules();
        REQUIRE(game.isGameOver() == true);
    }SECTION("Game ends when total score exceeds max score") {
        Game game;

        game.setScore(game.getMAX_SCORE() + 1);
        game.checkGameOverRules();
        REQUIRE(game.isGameOver() == true);
    }

//    SECTION("Game ends when time up exceeds max time") {
//        Game game;
//        std::this_thread::sleep_for(std::chrono::minutes(5));
//        game.checkGameOverRules();
//        REQUIRE(game.isGameOver() == false);
//    }

    SECTION("Test for 3 completed rows at level 1") {
        Game game;
        game.setLevel(1);
        game.addScore(3, 0);
        REQUIRE(game.getScore() == 900);
    }

    SECTION("Test for drop of 8 cases with no completed rows at level 2") {
        Game game;
        game.setLevel(2);
        game.addScore(0, 8);
        REQUIRE(game.getScore() == 16);
    }

    SECTION("Test for drop of 6 cases with 4 completed rows at level 3") {
        Game game;
        game.setLevel(3);
        game.addScore(4, 6);
        REQUIRE(game.getScore() == 14418);
    }

    SECTION("Test for no completed rows after a downward translation") {
        Game game;
        game.setLevel(1);
        game.addScore(0, 0);
        REQUIRE(game.getScore() == 0);
    }
}
