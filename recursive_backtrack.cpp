
#include <random>
#include "recursive_backtrack.h"

static std::random_device rnd{};

void build_maze(Cell *cell) {
    auto neighbors = cell->unvisited_neighbors();
    if (!neighbors.empty()) {
        Cell *neighbor = neighbors[(int)(rnd() % neighbors.size())];
        cell->link(neighbor);
        build_maze(neighbor);
        build_maze(cell);
    }
}

void build_rb_maze(Maze *maze) {
    int row = (int)(rnd() % maze->rows());
    int column = (int)(rnd() % maze->columns());
    build_maze(maze->get(row, column));
}
