cmake_minimum_required(VERSION 3.5)

add_executable(tests
        ../metier/Position.cpp
        ../metier/Direction.cpp
        ../metier/Brick.cpp
        ../metier/DefaultBricks.cpp
        ../metier/Board.cpp
        ../metier/Brick.cpp
        ../metier/Square.cpp
        ../metier/DefaultBricks.cpp
        ../metier/Bag.cpp
        ../metier/Game.cpp
        ../console/Controller.cpp
        ../console/View.cpp
        tests.cpp
)
target_include_directories(tests PRIVATE ../metier)

Include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.5.3 # or a later release
)

FetchContent_MakeAvailable(Catch2)
#list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)

target_link_libraries(tests Catch2::Catch2WithMain)
