//
// Created by alx on 7/4/23.
//

#include <algorithm>
#include "Maze.h"

void Maze::parse_nodes() {
    start = nullptr;
    finish = nullptr;
    node_map.clear();
    //Iterate all cells
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            if (maze[x][y] == MazeCellType::Wall) continue; // Ignore walls
            if (maze[x][y] == MazeCellType::Start) {//Make Start a node
                auto *node = new MazeNode;
                node->x = x;
                node->y = y;
                nodes.push_back(node);
                node_map[Vector2{x, y}] = node;
                start = node;
                continue;
            }
            if (maze[x][y] == MazeCellType::Finish) {//Make Finish a node
                auto *node = new MazeNode;
                node->x = x;
                node->y = y;
                nodes.push_back(node);
                node_map[Vector2{x, y}] = node;
                finish = node;
                continue;
            }
            //If it's Space, check if it should be added as a node
            //To be considered a node it must have either a single neighbor or at least one on each axis(vert,horiz)
            int vertical = 0;
            int horizontal = 0;
            //Iterate neighbours
            for (int i = x - 1; i < x + 2; i += 2) {
                if (i < 0 || i >= width) continue;
                if (maze[i][y] != MazeCellType::Wall)
                    horizontal++;
            }
            for (int j = y - 1; j < y + 2; j += 2) {
                if (j < 0 || j >= height) continue;
                if (maze[x][j] != MazeCellType::Wall)
                    vertical++;
            }
            if (vertical <= 2 && horizontal <= 2) {
                if (vertical == 2 && horizontal == 0) continue;
                if (vertical == 0 && horizontal == 2) continue;
                auto *node = new MazeNode;
                node->x = x;
                node->y = y;\
                nodes.push_back(node);
                node_map[Vector2{x, y}] = node;
            }
        }
    }
}

MazeNode *Maze::get_node(int x, int y) {
    return node_map[{x, y}];
}

void Maze::parse_edges() {
    std::vector<std::vector<int>> directions = {{1,  0},
                                                {-1, 0},
                                                {0,  1},
                                                {0,  -1}};
    for (auto node: nodes) {
        for (auto direction: directions) {
            int current_x = node->x + direction[0];
            int current_y = node->y + direction[1];
            if (current_x >= width || current_x < 0 || current_y >= height || current_y < 0) continue;
            int length = 1;
            while (maze[current_x][current_y] != MazeCellType::Wall) {
                MazeNode *possible_node = get_node(current_x, current_y);
                if (possible_node != nullptr) {
                    auto it = std::find(possible_node->nodes.begin(), possible_node->nodes.end(), node);
                    //if nodes are not already linked, link them
                    if (it == possible_node->nodes.end()) {
                        //add nodes in each others node list
                        node->nodes.push_back(possible_node);
                        possible_node->nodes.push_back(node);

                        //create edge containing both nodes
                        auto *edge = new MazeEdge;
                        edge->nodes[0] = node;
                        edge->nodes[1] = possible_node;
                        edge->length = length;

                        //add edge to edges and the nodes
                        edges.push_back(edge);
                        node->edges.push_back(edge);
                        possible_node->edges.push_back(edge);
                    }
                    break;
                }
                current_x += direction[0];
                current_y += direction[1];
                length++;
            }
        }
    }
}

Maze::Maze(int width, int height) : width(width), height(height) {
    maze = std::vector(width, std::vector(height, MazeCellType::Wall));
}

void Maze::parse() {
    for (auto node: nodes)
        delete node;
    for (auto edge: edges)
        delete edge;
    nodes.clear();
    edges.clear();
    parse_nodes();
    parse_edges();
}

int Maze::get_width() const { return width; }

int Maze::get_height() const { return height; }

Maze::~Maze() {
    for (auto node: nodes)
        delete node;
    for (auto edge: edges)
        delete edge;
}
