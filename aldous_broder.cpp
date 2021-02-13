
#include <cstdio>
#include <random>
#include <map>
#include "aldous_broder.h"

void build_aldousbroder_maze(Maze *maze) {
    std::random_device rnd{};
    std::map<Cell*,bool> visited;
    int maze_size = maze->rows() * maze->columns() - 1;

    int row = (int)(rnd() % maze->rows());
    int column = (int)(rnd() % maze->columns());
    Cell *cell = maze->get(row, column);

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
