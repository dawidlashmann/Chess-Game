cmake_minimum_required(VERSION 3.0)
project(chess_engine)

set(SOURCES
    engine/engine.cpp
    game_system/board.cpp
    game_system/game.cpp
    gui/window.cpp
    pieces/bishop.cpp
    pieces/king.cpp
    pieces/knight.cpp
    pieces/pawn.cpp
    pieces/piece.cpp
    pieces/queen.cpp
    pieces/rook.cpp
    main.cpp
)

find_package(SFML COMPONENTS graphics window system REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)

target_include_directories(${PROJECT_NAME} PRIVATE engine game_system gui pieces)