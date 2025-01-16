cmake_minimum_required(VERSION 3.5)

project(metier LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -pedantic-errors")

add_library(metier
    main.cpp
    Brick.h
    Position.h
    Square.h
    DefaultBricks.h
    Bag.h
    Direction.h
    Game.h
    Game.cpp
    Board.h
    Brick.cpp
    Position.cpp
    DefaultBricks.cpp
    Direction.cpp
    Bag.cpp
    Board.cpp
    Square.cpp
    Observer.h
    Subject.h
)
include(GNUInstallDirs)
install(TARGETS metier
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
