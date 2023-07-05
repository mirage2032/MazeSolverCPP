//
// Created by alx on 7/4/23.
//
#include <algorithm>
#include <unordered_set>
#include <queue>
#include "MazeSolver.h"

MazeSolver::MazePath MazeSolver::solveBFS(Maze* maze) {
    if (maze->start == nullptr || maze->finish == nullptr) return {};
    std::vector<MazePath> current_paths{};
    std::vector<MazePath> next_paths{};
    std::unordered_set<MazeNode *> visited{};

    current_paths.emplace_back((MazePath) {{maze->start}, {}, 0});
    visited.insert(maze->start);
    while (!current_paths.empty()) {
        for (auto path: current_paths) {
            MazeNode *last_node = path.node_path.back();
            for (auto edge: last_node->edges) {
                //get opposite node from edge
                MazeNode *neighboring_node = edge->nodes[0];
                if (neighboring_node == last_node) neighboring_node = edge->nodes[1];

                if (visited.find(neighboring_node) == visited.end()) { // If not visited
                    visited.insert(neighboring_node); // Add as visited

                    MazePath new_path = path;
                    new_path.node_path.push_back(neighboring_node);
                    new_path.edge_path.push_back(edge);
                    new_path.length += edge->length;
                    if (neighboring_node == maze->finish)
                        return new_path;
                    next_paths.push_back(new_path);
                }
            }
        }
        std::swap(current_paths, next_paths);
        next_paths.clear();
    }
    return {};

}
