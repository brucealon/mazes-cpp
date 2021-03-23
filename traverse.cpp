
#include <vector>

#include "traverse.h"

Traversal::Traversal(Maze *maze) :
    mMaze{ maze }
{}

void Traversal::reset() {
    visited.clear();
}

void Traversal::traverse_r(Cell *cell) {
    if (!visited[cell]) {
        visited[cell] = true;

        if (cell->is_linked(cell->north())) {
            traverse_r(cell->north());
        }
        if (cell->is_linked(cell->east())) {
            traverse_r(cell->east());
        }
        if (cell->is_linked(cell->south())) {
            traverse_r(cell->south());
        }
        if (cell->is_linked(cell->west())) {
            traverse_r(cell->west());
        }
    }
}

void Traversal::traverse(int row, int column) {
    reset();
    traverse_r(mMaze->get(row, column));
}

Maze *Traversal::maze() {
    return mMaze;
}

bool Traversal::is_visited(Cell *cell) {
    if (cell == nullptr) {
        return false;
    }

    return visited[cell];
}

bool Traversal::is_valid() {
    for (auto rowp = mMaze->begin(); rowp < mMaze->end(); rowp++) {
        for (auto cellp = rowp->begin(); cellp < rowp->end(); cellp++) {
            if (!visited[&(*cellp)]) {
                return false;
            }
        }
    }

    return true;
}

std::ostream& operator<<(std::ostream& os, Traversal& traversal) {
    Maze *maze = traversal.maze();

    os << "\u250C";
    for (int x = 0; x < maze->columns(); x++) {
        os << "\u2500\u2500\u2500";
        os << (x == (maze->columns() - 1) ? "\u2510" : "\u252C");
    }
    os << "\n";

    for (int row = 0; row < maze->rows(); row++) {
        os << "\u2502";
        for (int column = 0; column < maze->columns(); column++) {
            Cell *cell = maze->get(row, column);
            os << " " << (traversal.is_visited(cell) ? "\u22C6" : " ") << " ";
            os << (cell->is_linked(cell->east()) ? " " : "\u2502");
        }
        os << "\n";
        os << (row == (maze->rows() - 1) ? "\u2514" : "\u251C");
        for (int column = 0; column < maze->columns(); column++) {
            Cell *cell = maze->get(row, column);
            os << (cell->is_linked(cell->south()) ? "   " : "\u2500\u2500\u2500");
            if (row == (maze->rows() - 1)) {
                os << (row == (maze->columns() - 1) ? "\u2518" : "\u2534");
            } else {
                os << (row == (maze->columns() - 1) ? "\u2524" : "\u253C");
            }
        }
        os << "\n";
    }

    return os;
}
