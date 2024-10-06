cmake_minimum_required(VERSION 3.27)
project(untitled3)

set(CMAKE_CXX_STANDARD 20)

set(BUILD_SHARED_LIBS FALSE)

include(FetchContent)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY  https://github.com/fmtlib/fmt
        GIT_TAG         10.2.1
)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY  https://github.com/SFML/SFML
        GIT_TAG         2.6.1
)

FetchContent_MakeAvailable(SFML)

FetchContent_MakeAvailable(fmt)

add_executable(untitled3 main.cpp
        menu.cpp
        menu.h
        Options.cpp
        Options.h
        Game.cpp
        Game.h
        Word.cpp
        Word.h
)
target_link_libraries(untitled3 fmt)
target_link_libraries(untitled3 sfml-graphics)