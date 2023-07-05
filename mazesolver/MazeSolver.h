#ifndef MAZESOLVER_MAZESOLVER_H
#define MAZESOLVER_MAZESOLVER_H

#include <vector>
#include "Maze.h"


namespace MazeSolver {
    struct MazePath {
        std::vector<MazeNode *> node_path;
        std::vector<MazeEdge *> edge_path;
        int length;
    };
    typedef MazePath (*MazeSolver)(Maze *);

    MazePath solveBFS(Maze *maze);
};

#endif //MAZESOLVER_MAZESOLVER_H
