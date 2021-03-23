
#include <cstdio>
#include <random>
#include <map>
#include <vector>
#include "hunt_and_kill.h"

static std::random_device rnd{};
Cell *random_neighbor(std::vector<Cell*> neighbors) {
    return neighbors[(int)(rnd() % neighbors.size())];
}

Cell *hunt(Maze *maze) {
    for (auto rowp = maze->begin(); rowp != maze->end(); rowp++) {
        for (auto cellp = rowp->begin(); cellp != rowp->end(); cellp++) {
            Cell *cell = &(*cellp);
            if (cell->unvisited() && cell->has_visited_neighbors()) {
                return &(*cellp);
            }
        }
    }

    return nullptr;
}

void build_huntkill_maze(Maze *maze) {
    Cell *cell = maze->random_cell();

    while (cell) {
        auto neighbors = cell->unvisited_neighbors();
        if (neighbors.empty()) {
            cell = hunt(maze);
            if (cell) {
                neighbors = cell->visited_neighbors();
                Cell *neighbor = random_neighbor(neighbors);
                cell->link(neighbor);
            }
        } else {
            Cell *neighbor = random_neighbor(neighbors);
            cell->link(neighbor);
            cell = neighbor;
        }
    }
}
