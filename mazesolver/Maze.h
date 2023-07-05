//
// Created by alx on 7/4/23.
//

#ifndef MAZESOLVER_MAZE_H
#define MAZESOLVER_MAZE_H

#include <vector>
#include <unordered_map>
#include <set>

enum class MazeCellType {
    Start, Finish, Space, Wall
};
struct MazeEdge;

class Vector2 {
public:
    int x, y;

    Vector2(int x, int y) : x(x), y(y) {}

    bool operator==(const Vector2& other) const {
        return x == other.x && y == other.y;
    }
};

struct Vector2Hash {
    std::size_t operator()(const Vector2& vec) const {
        // Custom hash function implementation
        // Combine the hash values of x and y
        std::size_t h1 = std::hash<int>{}(vec.x);
        std::size_t h2 = std::hash<int>{}(vec.y);
        return h1 ^ (h2 << 1);
    }
};

struct MazeNode {
public:
    int x, y;
    std::vector<MazeNode *> nodes;
    std::vector<MazeEdge *> edges;
};

struct MazeEdge {
    MazeNode *nodes[2];
    int length;
};

class Maze {
    int width, height;

    void parse_nodes();

    MazeNode *get_node(int x, int y);

    void parse_edges();

public:
    std::vector<std::vector<MazeCellType>> maze;
    std::vector<MazeNode *> nodes;
    std::vector<MazeEdge *> edges;
    std::unordered_map<Vector2,MazeNode*,Vector2Hash> node_map;
    MazeNode* start = nullptr;
    MazeNode* finish = nullptr;
    Maze(int width, int height);

    void parse();

    int get_width() const;

    int get_height() const;

    ~Maze();
};


#endif //MAZESOLVER_MAZE_H
