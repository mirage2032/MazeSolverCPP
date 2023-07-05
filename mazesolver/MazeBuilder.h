//
// Created by alx on 7/5/23.
//

#ifndef MAZESOLVER_MAZEBUILDER_H
#define MAZESOLVER_MAZEBUILDER_H
#include <SFML/Graphics.hpp>
#include "Maze.h"
#include "MazeSolver.h"

class MazeBuilder {
private:
    sf::RenderWindow *window;
    sf::Image image;
    int scale;
    Maze *maze;
    MazeSolver::MazeSolver solver = nullptr;
    MazeSolver::MazePath solution;
    bool show_solution= false;
    void randomize_maze();
    sf::Image maze_to_image();
    void render_image(sf::Image image);
    void render_maze();
    void render_solution();
    void handle_input();
public:
    MazeBuilder(int width,int height, int scale);
    void Render();
    void Run();
    ~MazeBuilder();
};


#endif //MAZESOLVER_MAZEBUILDER_H
