//
// Created by alx on 7/5/23.
//
#include <random>
#include "MazeBuilder.h"

std::map<MazeCellType, sf::Color> colormap = {
        {MazeCellType::Start,  sf::Color{0x00, 0xff, 0x00, 0xff}},
        {MazeCellType::Finish, sf::Color{0xff, 0xff, 0x00, 0xff}},
        {MazeCellType::Space,  sf::Color{0x00, 0x00, 0xff, 0xff}},
        {MazeCellType::Wall,   sf::Color{0xff, 0x00, 0x00, 0xff}},
};

void MazeBuilder::randomize_maze() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::bernoulli_distribution dist(0.62);
    for (int x = 0; x < maze->get_width(); x++) {
        for (int y = 0; y < maze->get_height(); y++) {
            bool cellstate = dist(gen);
            if (cellstate) maze->maze[x][y] = MazeCellType::Space;
            else maze->maze[x][y] = MazeCellType::Wall;
        }
    }
    maze->parse();
    solution = {};
}

void drawLine(sf::Image &image, int x0, int y0, int x1, int y1, sf::Color color) {
    int dx = std::abs(x1 - x0);
    int dy = std::abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (x0 != x1 || y0 != y1) {
        image.setPixel(x0, y0, color);

        int err2 = 2 * err;

        if (err2 > -dy) {
            err -= dy;
            x0 += sx;
        }

        if (err2 < dx) {
            err += dx;
            y0 += sy;
        }
    }

    // Set the last pixel
    image.setPixel(x1, y1, color);
}


sf::Image MazeBuilder::maze_to_image() {
    const int width = maze->get_width();
    const int height = maze->get_height();

    auto *pixels = const_cast<sf::Uint8 *>(image.getPixelsPtr());

    MazeCellType *cellType = nullptr;
    sf::Uint8 *pixel = nullptr;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            cellType = &maze->maze[x][y];
            pixel = &pixels[(y * width + x) * 4];
            pixel[0] = colormap[*cellType].r;
            pixel[1] = colormap[*cellType].g;
            pixel[2] = colormap[*cellType].b;
            pixel[3] = colormap[*cellType].a;
        }
    }

    return image;
}

void MazeBuilder::render_image(sf::Image image) {
    sf::Texture texture;
    texture.loadFromImage(image);

    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setScale(scale, scale);

    window->draw(sprite);
}

void MazeBuilder::render_maze() {
    auto image = maze_to_image();
    render_image(image);
}

void MazeBuilder::render_solution() {

    image.create(maze->get_width(), maze->get_height(), {0, 0, 0, 0});
    for (auto edge: solution.edge_path) {
        drawLine(image, edge->nodes[0]->x, edge->nodes[0]->y, edge->nodes[1]->x, edge->nodes[1]->y, {0x00, 0xff, 0xff});
    }
    render_image(image);
}

void MazeBuilder::handle_input() {
    sf::Event event;

    while (window->pollEvent(event)) {

        if (event.type == sf::Event::Closed)
            window->close();
        if (event.type == sf::Event::KeyPressed) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
            if (event.key.code == sf::Keyboard::I) { //SET ENTRANCE
                if (maze->start != nullptr) maze->maze[maze->start->x][maze->start->y] = MazeCellType::Space;
                maze->maze[mousePosition.x / scale][mousePosition.y / scale] = MazeCellType::Start;
                maze->parse();
                solution = {};
                if (show_solution)
                    solution = solver(maze);
            }
            if (event.key.code == sf::Keyboard::O) { //SET FINISH
                if (maze->finish != nullptr) maze->maze[maze->finish->x][maze->finish->y] = MazeCellType::Space;
                maze->maze[mousePosition.x / scale][mousePosition.y / scale] = MazeCellType::Finish;
                maze->parse();
                solution = {};
                if (show_solution)
                    solution = solver(maze);
            }
            if (event.key.code == sf::Keyboard::W) { //SET WALL
                maze->maze[mousePosition.x / scale][mousePosition.y / scale] = MazeCellType::Wall;
                maze->parse();
                if (show_solution)
                    solution = solver(maze);
            }
            if (event.key.code == sf::Keyboard::S) { //SET SPACE
                maze->maze[mousePosition.x / scale][mousePosition.y / scale] = MazeCellType::Space;
                maze->parse();
                if (show_solution)
                    solution = solver(maze);
            }
            if (event.key.code == sf::Keyboard::L) { //SHOW SOLUTION
                show_solution = !show_solution;
                if (show_solution) {
                    if (solver == nullptr) { solver = MazeSolver::solveBFS; }
                    solution = solver(maze);
                }
            }
//            if (event.key.code == sf::Keyboard::P) { //CHANGE SOLVER
//                solution = solver(maze);
//            }
            if (event.key.code == sf::Keyboard::R) { //RANDOMIZE MAZE
                randomize_maze();
            }
        }
    }
}

MazeBuilder::MazeBuilder(int width, int height, int scale) : scale(scale) {
    maze = new Maze(width, height);
    window = new sf::RenderWindow(sf::VideoMode(width * scale, height * scale), "Maze Builder");
    image.create(width, height);
}

void MazeBuilder::Render() {
    window->clear({0x25, 0x25, 0x25, 0xff});
    handle_input();
    render_maze();
    if (show_solution)
        render_solution();
    window->display();
}

void MazeBuilder::Run() {
    while (window->isOpen()) {
        Render();
    }
}

MazeBuilder::~MazeBuilder() {
    delete maze;
    delete window;
}
