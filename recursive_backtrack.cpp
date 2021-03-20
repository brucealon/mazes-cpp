
#include <random>
#include <stack>
#include <vector>
#include "recursive_backtrack.h"

static std::random_device rnd{};

void build_rb_maze(Maze *maze) {
    std::stack<Cell*> stack;

    int row = (int)(rnd() % maze->rows());
    int column = (int)(rnd() % maze->columns());
    Cell *cell = maze->get(row, column);
    stack.push(cell);

    while (!stack.empty()) {
        cell = stack.top();
        auto neighbors = cell->unvisited_neighbors();
        if (neighbors.empty()) {
            stack.pop();
        } else {
            Cell *neighbor = neighbors[(int)(rnd() % neighbors.size())];
            cell->link(neighbor);
            stack.push(neighbor);
        }
    }
}
