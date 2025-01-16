cmake_minimum_required(VERSION 3.5)

project(console LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -pedantic-errors")

include_directories(../metier)

add_executable(console
    main.cpp
    View.h
    View.cpp
    Controller.h
    Controller.cpp
)

target_link_libraries(console PRIVATE metier)

include(GNUInstallDirs)
install(TARGETS console
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
