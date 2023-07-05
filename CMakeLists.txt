cmake_minimum_required(VERSION 3.25)
project(MazeSolver)

set(CMAKE_CXX_STANDARD 17)
find_package(SFML COMPONENTS system window graphics REQUIRED)
add_executable(MazeSolver main.cpp mazesolver/MazeSolver.cpp mazesolver/MazeSolver.h mazesolver/Maze.cpp mazesolver/Maze.h mazesolver/MazeBuilder.cpp mazesolver/MazeBuilder.h)
target_link_libraries(MazeSolver sfml-system sfml-window sfml-graphics)
