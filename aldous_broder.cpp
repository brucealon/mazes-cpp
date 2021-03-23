
#include <cstdio>
#include <random>
#include <map>
#include "aldous_broder.h"

void build_aldousbroder_maze(Maze *maze) {
    std::random_device rnd{};
    std::map<Cell*,bool> visited;
    int maze_size = maze->rows() * maze->columns() - 1;

    Cell *cell = maze->random_cell();

    while ((int)visited.size() <= maze_size) {
        std::vector<Cell*> neighbors = cell->neighbors();
        Cell *neighbor = neighbors[(int)(rnd() % neighbors.size())];
        if (!visited[neighbor]) {
            cell->link(neighbor);
            visited[neighbor] = true;
        }
        cell = neighbor;
    }
}
